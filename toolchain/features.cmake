
macro(feature_parse_name_value feature name value)
    string(REPLACE "=" ";" feature_tokens ${feature})
    list(GET feature_tokens 0 ${name})
    list(GET feature_tokens 1 ${value})
endmacro()

macro(feature_get_value feature value)
    if (DEFINED ${feature})
        set(${value} ${${feature}})
    elseif (DEFINED ENV{${feature}})
        set(${value} $ENV{${feature}})
    else()
        set(${value} UNDEFINED)
    endif ()
endmacro()

set(FEATURE_TOGGLES
    LD_LOADER_PATH="/lib/ld-linux-aarch64.so.1"
    LOG_ENABLE_RA02=0
    LOG_ENABLE_MAIN=0
)

foreach (feature ${FEATURE_TOGGLES})
    feature_parse_name_value(${feature} name default)
    feature_get_value(${name} val)

    if ("${val}" STREQUAL "UNDEFINED")
        message(STATUS "Feature ${name} using default value ${default}")
        add_compile_definitions(${feature})
    else ()
        message(STATUS "Feature ${name} overridden, value ${val}")
        if (${name} STREQUAL LD_LOADER_PATH)
            add_compile_definitions(${name}="${val}")
        else()
            add_compile_definitions(${name}=${val})
        endif()
    endif ()
endforeach ()
