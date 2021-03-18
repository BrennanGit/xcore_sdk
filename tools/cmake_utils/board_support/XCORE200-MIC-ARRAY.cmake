set(FREERTOS_PORT "XCORE200")

add_compile_definitions(
    XCORE200_MIC_ARRAY=1
    PLATFORM_SUPPORTS_TILE_0=1
    PLATFORM_SUPPORTS_TILE_1=1
    PLATFORM_SUPPORTS_TILE_2=0
    PLATFORM_SUPPORTS_TILE_3=0
    USB_TILE_NO=1
    USB_TILE=tile[USB_TILE_NO]
    XUD_SERIES_SUPPORT=XUD_X200_SERIES
)