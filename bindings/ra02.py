import ctypes

RA02_DYNLIB = None

class spi_cfg_t(ctypes.Structure):
    _fields_ = [
        ('speed', ctypes.c_uint32),
        ('delay_us', ctypes.c_uint16),
        ('bits_per_word', ctypes.c_uint8),
    ]

class spi_t(ctypes.Structure):
    _fields_ = [
        ('cfg', spi_cfg_t),
        ('fd', ctypes.c_int),
    ]

class Spi:
    def __init__(self, spidev: str = ''):
        self.spi = spi_t()

        if spidev:
            self.init(spidev)

    def __del__(self):
        self.deinit()

    def init(self, spidev: str):
        cfg = spi_cfg_t()

        RA02_DYNLIB.spi_cfg_default(ctypes.byref(cfg))
        RA02_DYNLIB.spi_init(ctypes.byref(self.spi), ctypes.byref(cfg), spidev.encode('utf-8'))

    def deinit(self):
        RA02_DYNLIB.spi_deinit(ctypes.byref(self.spi))

    def transceive(self, data: list[int]) -> list[int]:
        tx_buf = (ctypes.c_uint8 * len(data))(*data)
        rx_buf = (ctypes.c_uint8 * len(data))()

        RA02_DYNLIB.spi_transcieve(
            ctypes.byref(self.spi),
            tx_buf,
            rx_buf,
            ctypes.c_size_t(len(data))
        )

        return list(rx_buf)


class timeout_t(ctypes.Structure):
    _fields_ = [
        ('start', ctypes.c_uint64),
        ('duration', ctypes.c_uint64),
    ]

class Timeout:
    def __init__(self, duration: int = 0):
        self.timeout = timeout_t()

        if duration:
            self.start(duration)

    def start(self, duration: int):
        RA02_DYNLIB.timeout_start(ctypes.byref(self.timeout), duration)

    def restart(self):
        RA02_DYNLIB.timeout_restart(ctypes.byref(self.timeout))

    def is_expired(self):
        return RA02_DYNLIB.timeout_is_expired(ctypes.byref(self.timeout))

    def expire(self):
        RA02_DYNLIB.timeout_expire(ctypes.byref(self.timeout))

class ra02_cfg_t(ctypes.Structure):
    _fields_ = [
        ('spi', ctypes.POINTER(spi_t)),
    ]

class ra02_t(ctypes.Structure):
    _fields_ = [
        ('spi', ctypes.POINTER(spi_t)),
        ('irq_flags', ctypes.c_uint8),
    ]


class Ra02:
    MAX_PAYLOAD = 64

    def __init__(self, spi: Spi):
        self.ra02 = ra02_t()

        if spi:
            self.init(spi)

    def __del__(self):
        self.deinit()

    def init(self, spi: Spi):
        self.spi = spi

        cfg = ra02_cfg_t(spi=ctypes.pointer(spi.spi))

        RA02_DYNLIB.ra02_init(ctypes.byref(self.ra02), ctypes.byref(cfg))

    def deinit(self):
        RA02_DYNLIB.ra02_deinit(ctypes.byref(self.ra02))

    def reset(self):
        RA02_DYNLIB.ra02_reset(ctypes.byref(self.ra02))

    def sleep(self):
        RA02_DYNLIB.ra02_sleep(ctypes.byref(self.ra02))

    def set_freq(self, freq: int):
        RA02_DYNLIB.ra02_set_freq(ctypes.byref(self.ra02), ctypes.c_uint32(freq))

    def get_power(self):
        db = ctypes.c_uint8()
        RA02_DYNLIB.ra02_get_power(ctypes.byref(self.ra02), ctypes.byref(db))
        return db.value

    def set_power(self, db: int):
        RA02_DYNLIB.ra02_set_power(ctypes.byref(self.ra02), ctypes.c_uint32(db))

    def set_sync_word(self, sync_word: int):
        RA02_DYNLIB.ra02_set_sync_word(ctypes.byref(self.ra02), ctypes.c_uint32(sync_word))

    def set_baudrate(self, baudrate: int):
        RA02_DYNLIB.ra02_set_baudrate(ctypes.byref(self.ra02), ctypes.c_uint32(baudrate))

    def set_bandwidth(self, bandwidth: int):
        RA02_DYNLIB.ra02_set_bandwidth(ctypes.byref(self.ra02), ctypes.c_uint32(bandwidth))

    def set_preamble(self, preamble: int):
        RA02_DYNLIB.ra02_set_preamble(ctypes.byref(self.ra02), ctypes.c_uint32(preamble))

    def get_rssi(self):
        rssi = ctypes.c_uint8()
        RA02_DYNLIB.ra02_get_rssi(ctypes.byref(self.ra02), ctypes.byref(rssi))
        return rssi.value

    def poll_irq_flags(self):
        RA02_DYNLIB.ra02_poll_irq_flags(ctypes.byref(self.ra02))

    def send(self, data: list[int]) -> list[int]:
        buf = (ctypes.c_uint8 * len(data))(*data)

        return RA02_DYNLIB.ra02_send(ctypes.byref(self.ra02), buf, ctypes.c_size_t(len(data)))

    def recv(self, timeout: Timeout) -> list[int]:
        buf = (ctypes.c_uint8 * self.MAX_PAYLOAD)()
        size = ctypes.c_size_t(self.MAX_PAYLOAD)

        RA02_DYNLIB.ra02_recv(ctypes.byref(self.ra02), buf, ctypes.byref(size), ctypes.byref(timeout.timeout))

        return list(buf)[:size.value]


def __init__(dynlib_path: str):
    global RA02_DYNLIB
    RA02_DYNLIB = ctypes.cdll.LoadLibrary(dynlib_path)

    RA02_DYNLIB.spi_cfg_default.argtypes = [ctypes.POINTER(spi_cfg_t)]
    RA02_DYNLIB.spi_cfg_default.restype = ctypes.c_int

    RA02_DYNLIB.spi_init.argtypes = [ctypes.POINTER(spi_t), ctypes.POINTER(spi_cfg_t), ctypes.c_char_p]
    RA02_DYNLIB.spi_init.restype = ctypes.c_int

    RA02_DYNLIB.spi_deinit.argtypes = [ctypes.POINTER(spi_t)]
    RA02_DYNLIB.spi_deinit.restype = ctypes.c_int

    RA02_DYNLIB.spi_transcieve.argtypes = [
        ctypes.POINTER(spi_t),
        ctypes.POINTER(ctypes.c_uint8),
        ctypes.POINTER(ctypes.c_uint8),
        ctypes.c_size_t
    ]
    RA02_DYNLIB.spi_transcieve.restype = ctypes.c_int

    RA02_DYNLIB.timeout_start.argtypes = [ctypes.POINTER(timeout_t), ctypes.c_uint64]
    RA02_DYNLIB.timeout_start.restype = None

    RA02_DYNLIB.timeout_restart.argtypes = [ctypes.POINTER(timeout_t)]
    RA02_DYNLIB.timeout_restart.restype = None

    RA02_DYNLIB.timeout_is_expired.argtypes = [ctypes.POINTER(timeout_t)]
    RA02_DYNLIB.timeout_is_expired.restype = ctypes.c_bool

    RA02_DYNLIB.timeout_expire.argtypes = [ctypes.POINTER(timeout_t)]
    RA02_DYNLIB.timeout_expire.restype = None

    RA02_DYNLIB.ra02_init.argtypes = [ctypes.POINTER(ra02_t), ctypes.POINTER(ra02_cfg_t)]
    RA02_DYNLIB.ra02_init.restype = ctypes.c_int

    RA02_DYNLIB.ra02_deinit.argtypes = [ctypes.POINTER(ra02_t)]
    RA02_DYNLIB.ra02_deinit.restype = ctypes.c_int

    RA02_DYNLIB.ra02_reset.argtypes = [ctypes.POINTER(ra02_t)]
    RA02_DYNLIB.ra02_reset.restype = ctypes.c_int

    RA02_DYNLIB.ra02_sleep.argtypes = [ctypes.POINTER(ra02_t)]
    RA02_DYNLIB.ra02_sleep.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_freq.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_freq.restype = ctypes.c_int

    RA02_DYNLIB.ra02_get_power.argtypes = [ctypes.POINTER(ra02_t), ctypes.POINTER(ctypes.c_uint32)]
    RA02_DYNLIB.ra02_get_power.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_power.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_power.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_sync_word.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_sync_word.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_baudrate.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_baudrate.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_bandwidth.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_bandwidth.restype = ctypes.c_int

    RA02_DYNLIB.ra02_set_preamble.argtypes = [ctypes.POINTER(ra02_t), ctypes.c_uint32]
    RA02_DYNLIB.ra02_set_preamble.restype = ctypes.c_int

    RA02_DYNLIB.ra02_get_rssi.argtypes = [ctypes.POINTER(ra02_t), ctypes.POINTER(ctypes.c_uint8)]
    RA02_DYNLIB.ra02_get_rssi.restype = ctypes.c_int

    RA02_DYNLIB.ra02_poll_irq_flags.argtypes = [ctypes.POINTER(ra02_t)]
    RA02_DYNLIB.ra02_poll_irq_flags.restype = ctypes.c_int

    RA02_DYNLIB.ra02_send.argtypes = [ctypes.POINTER(ra02_t), ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t]
    RA02_DYNLIB.ra02_send.restype = ctypes.c_int

    RA02_DYNLIB.ra02_recv.argtypes = [ctypes.POINTER(ra02_t), ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_size_t), ctypes.POINTER(timeout_t)]
    RA02_DYNLIB.ra02_recv.restype = ctypes.c_int
