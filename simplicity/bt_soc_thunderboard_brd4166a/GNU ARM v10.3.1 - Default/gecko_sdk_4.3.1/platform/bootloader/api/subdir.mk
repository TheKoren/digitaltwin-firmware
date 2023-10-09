################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk/platform/bootloader/api/btl_interface.c \
C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk/platform/bootloader/api/btl_interface_storage.c 

OBJS += \
./gecko_sdk_4.3.1/platform/bootloader/api/btl_interface.o \
./gecko_sdk_4.3.1/platform/bootloader/api/btl_interface_storage.o 

C_DEPS += \
./gecko_sdk_4.3.1/platform/bootloader/api/btl_interface.d \
./gecko_sdk_4.3.1/platform/bootloader/api/btl_interface_storage.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.1/platform/bootloader/api/btl_interface.o: C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk/platform/bootloader/api/btl_interface.c gecko_sdk_4.3.1/platform/bootloader/api/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFR32MG12P332F1024GL125=1' '-DSL_APP_PROPERTIES=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD4166A"' '-DSL_BOARD_REV="D03"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CLIENT=1' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DBRD4166A_SUPPORT=1' -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\config" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\config\btconf" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\autogen" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\brd4166a" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG12P/Include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_assert" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_log" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_timer" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//protocol/bluetooth/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//protocol/bluetooth/bgstack/ll/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/bmp280/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/bmp280/bosch/BMP280_driver" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader/api" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/button/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/ccs811/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/ccs811/firmware" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_aio" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_battery" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_device_information" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_gas" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_hall" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_imu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_light" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_pressure" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_rgb" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_rht" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_sound" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/i2cspm/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/icm20648/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/imu/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/in_place_ota_dfu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/library" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/mic/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/mpu/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/power_manager/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/power_supply" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/pressure/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_psa_driver/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/common" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ble" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/wmbus" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/zwave" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/chip/efr32/efr32xg1x" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/sidewalk" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions/efr32xg1x" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_pti" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_gas" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_hall" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_imu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_light" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_pressure" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_rht" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_select" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_sound" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si1133/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si70xx/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si7210/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/silicon_labs/silabs_core/memory_manager" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_protocol_crypto/src" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fno-builtin-printf -fno-builtin-sprintf --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.1/platform/bootloader/api/btl_interface.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.1/platform/bootloader/api/btl_interface_storage.o: C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk/platform/bootloader/api/btl_interface_storage.c gecko_sdk_4.3.1/platform/bootloader/api/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DEFR32MG12P332F1024GL125=1' '-DSL_APP_PROPERTIES=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD4166A"' '-DSL_BOARD_REV="D03"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CLIENT=1' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DBRD4166A_SUPPORT=1' -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\config" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\config\btconf" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\autogen" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a" -I"D:\Workspaces\digitaltwin-firmware\simplicity\bt_soc_thunderboard_brd4166a\brd4166a" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG12P/Include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_assert" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_log" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/common/util/app_timer" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//protocol/bluetooth/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//protocol/bluetooth/bgstack/ll/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/bmp280/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/bmp280/bosch/BMP280_driver" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/bootloader/api" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/button/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/ccs811/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/ccs811/firmware" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_aio" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_battery" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_device_information" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_gas" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_hall" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_imu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_light" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_pressure" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_rgb" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_rht" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/gatt_service_sound" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/i2cspm/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/icm20648/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/imu/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/in_place_ota_dfu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_mbedtls_support/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/include" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/mbedtls/library" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/mic/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/mpu/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/power_manager/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/power_supply" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/pressure/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/third_party/printf/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_psa_driver/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/common" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ble" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/wmbus" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/zwave" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/chip/efr32/efr32xg1x" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/protocol/sidewalk" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/pa-conversions/efr32xg1x" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/radio/rail_lib/plugin/rail_util_pti" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_gas" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_hall" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_imu" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_light" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_pressure" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_rht" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_select" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//app/bluetooth/common/sensor_sound" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si1133/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si70xx/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/si7210/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//util/silicon_labs/silabs_core/memory_manager" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/security/sl_component/sl_protocol_crypto/src" -I"C:/Users/36302/SimplicityStudio/SDKs/gecko_sdk//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fno-builtin-printf -fno-builtin-sprintf --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.1/platform/bootloader/api/btl_interface_storage.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


