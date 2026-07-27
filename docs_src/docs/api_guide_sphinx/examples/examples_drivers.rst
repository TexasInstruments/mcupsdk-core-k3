SOC and Board Peripheral Drivers
===================================

.. toctree::
   :maxdepth: 1
   :hidden:
   :titlesonly:

   drivers/aasrc_multichannel_playback
   drivers/aasrc_sinewave_conversion
   drivers/aasrc_stereo_playback
   drivers/adc_singleshot
   drivers/ddr_ecc_test_main_esm
   drivers/ddr_memtester
   drivers/ddr_perf
   drivers/dss_colorbar_test
   drivers/dss_display_share
   drivers/dss_display_test
   drivers/dss_safety_test
   drivers/dss_splash_demo
   drivers/ecap_apwm_mode
   drivers/ecap_epwm_loopback
   drivers/epwm_duty_cycle
   drivers/epwm_duty_cycle_sync
   drivers/flc_basic
   drivers/gpio_input_interrupt
   drivers/gpio_led_blink
   drivers/gpmc_flash_io
   drivers/i2c_led_blink
   drivers/i2c_memory_read
   drivers/i2c_read
   drivers/i2c_temperature
   drivers/ipc_notify_echo
   drivers/ipc_rpmessage_echo
   drivers/ipc_rpmessage_linux_echo
   drivers/ipc_rpmessage_linux_audio_filter_offload
   drivers/ipc_rpmessage_qnx_echo
   drivers/ipc_rpmessage_rtos_audio_filter_offload
   drivers/mcasp_early_chime
   drivers/mcan_external_read_write
   drivers/mcan_loopback_interrupt
   drivers/mcan_loopback_polling
   drivers/mcasp_audio_presentation_time
   drivers/mcasp_aec_multichannel_playback
   drivers/mcasp_chime_tad5212
   drivers/mcasp_multichannel_in_stereo_out
   drivers/mcasp_multichannel_playback
   drivers/mcasp_stereo_playback
   drivers/mcspi_loopback
   drivers/mcspi_loopback_dma
   drivers/mcspi_loopback_turbo_mode
   drivers/mcspi_performance_8bit
   drivers/mcspi_performance_32bit
   drivers/mmcsd_raw_io
   drivers/ospi_flash_diag
   drivers/ospi_flash_io
   drivers/ospi_phy_grapher_uart
   drivers/pmic_qa_watchdog_interrupt
   drivers/pmic_qa_watchdog_reset
   drivers/pmic_trigger_watchdog_interrupt
   drivers/pmic_trigger_watchdog_reset
   drivers/pmic_user_reg_cfg
   drivers/pmu_multievent
   drivers/rl2_basic
   drivers/rtc_led_blink
   drivers/eeprom_read_write
   drivers/eqep_capture
   drivers/eqep_frequency_measurement
   drivers/eqep_position_speed
   drivers/mcasp_loopback
   drivers/mcasp_loopback_ext_hclk
   drivers/mmcsd_file_io
   drivers/sciclient_get_version
   drivers/spinlock_example
   tisp/fft2d_rtos_dsp_offload
   tisp/fft2d_linux_dsp_offload
   tisp/sigchain_dsp_rt/sigchain_top
   tisp/sigchain_dsp_rt/sigchain_biquad_cascade
   tisp/sigchain_dsp_rt/sigchain_biquad_linux_example
   tisp/sigchain_dsp_rt/sigchain_eq_gain_mute
   tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch
   tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain
   drivers/uart_echo_dma
   drivers/udma_chaining
   drivers/udma_memcpy_interrupt
   drivers/udma_memcpy_polling
   drivers/udma_sw_trigger
   drivers/uart_echo
   drivers/uart_echo_bcdma
   drivers/uart_echo_callback
   drivers/uart_echo_dma_multi_instance
   drivers/uart_echo_low_latency_interrupt
   drivers/uart_echo_low_latency_polling
   drivers/watchdog_interrupt_mode
   drivers/csirx_capture_test
   drivers/csirx_imx219_test
   drivers/mcasp_playback_codec_aic31
   drivers/sciclient_ccs_init
   drivers/hyper_ram_ecc_test
   drivers/hyper_ram_ecc_esm_test
   drivers/hyper_ram_read_write
   drivers/ipc_notify_echo_optishare
   drivers/ddr_ecc_test_mcu_esm

This page lists all the examples related to usage of SOC and board peripheral drivers.

.. only:: SOC_AM62X

   **DDR**
      - :doc:`DDR ECC Test MAIN ESM <drivers/ddr_ecc_test_main_esm>`
      - :doc:`DDR ECC Test MCU ESM <drivers/ddr_ecc_test_mcu_esm>`
      - :doc:`DDR PERF Test <drivers/ddr_perf>`

   **DSS**
      - :doc:`DSS Colorbar Test <drivers/dss_colorbar_test>`
      - :doc:`DSS Display Test <drivers/dss_display_test>`
      - :doc:`DSS Safety Test <drivers/dss_safety_test>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **EQEP**
      - :doc:`EQEP Capture <drivers/eqep_capture>`
      - :doc:`EQEP frequency measurement <drivers/eqep_frequency_measurement>`
      - :doc:`EQEP Position Speed <drivers/eqep_position_speed>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **GPMC**
      - :doc:`GPMC Flash IO <drivers/gpmc_flash_io>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC RP Message Linux Echo <drivers/ipc_rpmessage_linux_echo>`
      - :doc:`IPC RP Message QNX Echo <drivers/ipc_rpmessage_qnx_echo>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCASP**
      - :doc:`MCASP Loopback <drivers/mcasp_loopback>`
      - :doc:`MCASP Playback <drivers/mcasp_playback_codec_aic31>`
      - :doc:`MCASP Loopback External HCLK <drivers/mcasp_loopback_ext_hclk>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`
      - :doc:`MMCSD FILE IO <drivers/mmcsd_file_io>`

   **OSPI**
      - :doc:`OSPI Flash Diagnostic <drivers/ospi_flash_diag>`
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`

   **PMU**
      - :doc:`PMU Multievent <drivers/pmu_multievent>`

   **RTC**
      - :doc:`RTC LED Blink <drivers/rtc_led_blink>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`

   **SPINLOCK**
      - :doc:`Spinlock Example <drivers/spinlock_example>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo DMA <drivers/uart_echo_dma>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **WATCHDOG**
      - :doc:`Watchdog interrupt mode <drivers/watchdog_interrupt_mode>`

.. only:: SOC_AM62AX

   **CSI-RX**
      - :doc:`CSIRX CAPTURE TEST <drivers/csirx_capture_test>`
      - :doc:`CSIRX CAPTURE TEST <drivers/csirx_imx219_test>`

   **DDR**
      - :doc:`DDR ECC Test MAIN ESM <drivers/ddr_ecc_test_main_esm>`
      - :doc:`DDR PERF Test <drivers/ddr_perf>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **EQEP**
      - :doc:`EQEP Capture <drivers/eqep_capture>`
      - :doc:`EQEP frequency measurement <drivers/eqep_frequency_measurement>`
      - :doc:`EQEP Position Speed <drivers/eqep_position_speed>`

   **EEPROM**
      - :doc:`EEPROM Read Write <drivers/eeprom_read_write>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC RP Message Linux Echo <drivers/ipc_rpmessage_linux_echo>`
      - :doc:`IPC RP Message QNX Echo <drivers/ipc_rpmessage_qnx_echo>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCASP**
      - :doc:`MCASP Loopback <drivers/mcasp_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCASP Loopback External HCLK <drivers/mcasp_loopback_ext_hclk>`
      - :doc:`MCASP Playback <drivers/mcasp_playback_codec_aic31>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`
      - :doc:`MMCSD FILE IO <drivers/mmcsd_file_io>`

   **OSPI**
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`

   **PMU**
      - :doc:`PMU Multievent <drivers/pmu_multievent>`

   **RTC**
      - :doc:`RTC LED Blink <drivers/rtc_led_blink>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo DMA <drivers/uart_echo_dma>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **WATCHDOG**
      - :doc:`Watchdog interrupt mode <drivers/watchdog_interrupt_mode>`

.. only:: SOC_AM62DX

   **DDR**
      - :doc:`DDR ECC Test MAIN ESM <drivers/ddr_ecc_test_main_esm>`
      - :doc:`DDR Memtester <drivers/ddr_memtester>`
      - :doc:`DDR PERF Test <drivers/ddr_perf>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **EQEP**
      - :doc:`EQEP Capture <drivers/eqep_capture>`
      - :doc:`EQEP frequency measurement <drivers/eqep_frequency_measurement>`
      - :doc:`EQEP Position Speed <drivers/eqep_position_speed>`

   **EEPROM**
      - :doc:`EEPROM Read Write <drivers/eeprom_read_write>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Memory Read <drivers/i2c_memory_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC RP Message Linux Echo <drivers/ipc_rpmessage_linux_echo>`
      - :doc:`IPC RP Message Linux Audio Filter Offload <drivers/ipc_rpmessage_linux_audio_filter_offload>`
      - :doc:`IPC RP Message RTOS Audio Filter Offload <drivers/ipc_rpmessage_rtos_audio_filter_offload>`

   **MCAN**
      - :doc:`MCAN External Read Write <drivers/mcan_external_read_write>`
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCASP**
      - :doc:`MCASP Audio Presentation Time <drivers/mcasp_audio_presentation_time>`
      - :doc:`MCASP AEC Multichannel Playback <drivers/mcasp_aec_multichannel_playback>`
      - :doc:`MCASP Chime <drivers/mcasp_chime_tad5212>`
      - :doc:`MCASP Loopback <drivers/mcasp_loopback>`
      - :doc:`MCASP Multichannel in Stereo out <drivers/mcasp_multichannel_in_stereo_out>`
      - :doc:`MCASP Multichannel Playback <drivers/mcasp_multichannel_playback>`
      - :doc:`MCASP Stereo Playback <drivers/mcasp_stereo_playback>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`
      - :doc:`MCSPI Loopback Turbo Mode <drivers/mcspi_loopback_turbo_mode>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`
      - :doc:`MMCSD FILE IO <drivers/mmcsd_file_io>`

   **OSPI**
      - :doc:`OSPI Flash Diagnostic <drivers/ospi_flash_diag>`
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`
      - :doc:`OSPI PHY Grapher UART <drivers/ospi_phy_grapher_uart>`

   **PMIC**
      - :doc:`PMIC Q&A watchdog interrupt example <drivers/pmic_qa_watchdog_interrupt>`
      - :doc:`PMIC Q&A watchdog reset example <drivers/pmic_qa_watchdog_reset>`
      - :doc:`PMIC trigger watchdog interrupt example <drivers/pmic_trigger_watchdog_interrupt>`
      - :doc:`PMIC trigger watchdog reset example <drivers/pmic_trigger_watchdog_reset>`
      - :doc:`PMIC user register configuration example <drivers/pmic_user_reg_cfg>`

   **PMU**
      - :doc:`PMU Multievent <drivers/pmu_multievent>`

   **RTC**
      - :doc:`RTC LED Blink <drivers/rtc_led_blink>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`

   **SPINLOCK**
      - :doc:`Spinlock Example <drivers/spinlock_example>`

   **TISP**
      - :doc:`TISP 2D FFT DSP Offload <tisp/fft2d_rtos_dsp_offload>`
      - :doc:`TISP Linux 2D FFT Offload <tisp/fft2d_linux_dsp_offload>`
      - :doc:`TISP Real-Time Signal Chain Examples <tisp/sigchain_dsp_rt/sigchain_top>`
      - :doc:`Cascade Biquad Parametric EQ <tisp/sigchain_dsp_rt/sigchain_biquad_cascade>`
      - :doc:`Cascade Biquad Parametric EQ (Linux) <tisp/sigchain_dsp_rt/sigchain_biquad_linux_example>`
      - :doc:`EQ, Gain, and Mute <tisp/sigchain_dsp_rt/sigchain_eq_gain_mute>`
      - :doc:`Router with FFT/IFFT DSP Processing (8ch to 12ch) <tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch>`
      - :doc:`Comprehensive Audio Chain (8ch to 12ch) <tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo DMA <drivers/uart_echo_dma>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **WATCHDOG**
      - :doc:`Watchdog interrupt mode <drivers/watchdog_interrupt_mode>`

.. only:: SOC_AM275X

   **AASRC**
      - :doc:`AASRC Multichannel Playback <drivers/aasrc_multichannel_playback>`
      - :doc:`AASRC Sinewave Conversion <drivers/aasrc_sinewave_conversion>`
      - :doc:`AASRC Stereo Playback <drivers/aasrc_stereo_playback>`

   **ADC**
      - :doc:`ADC Singleshot <drivers/adc_singleshot>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **EEPROM**
      - :doc:`EEPROM Read Write <drivers/eeprom_read_write>`

   **FLC**
      - :doc:`FLC Example <drivers/flc_basic>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **HYPERRAM**
      - :doc:`Hyper RAM ECC Test <drivers/hyper_ram_ecc_test>`
      - :doc:`Hyper RAM ECC ESM Test <drivers/hyper_ram_ecc_esm_test>`
      - :doc:`Hyper RAM Read Write <drivers/hyper_ram_read_write>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC Notify Echo Example With OptiShare <drivers/ipc_notify_echo_optishare>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCASP**
      - :doc:`MCASP Loopback <drivers/mcasp_loopback>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`
      - :doc:`MMCSD FILE IO <drivers/mmcsd_file_io>`

   **OSPI**
      - :doc:`OSPI Flash Diagnostic <drivers/ospi_flash_diag>`
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`

   **PMIC**
      - :doc:`PMIC Q&A watchdog interrupt example <drivers/pmic_qa_watchdog_interrupt>`
      - :doc:`PMIC Q&A watchdog reset example <drivers/pmic_qa_watchdog_reset>`
      - :doc:`PMIC trigger watchdog interrupt example <drivers/pmic_trigger_watchdog_interrupt>`
      - :doc:`PMIC trigger watchdog reset example <drivers/pmic_trigger_watchdog_reset>`
      - :doc:`PMIC user register configuration example <drivers/pmic_user_reg_cfg>`

   **PMU**
      - :doc:`PMU Multievent <drivers/pmu_multievent>`

   **RL2**
      - :doc:`RL2 Example <drivers/rl2_basic>`

   **RTC**
      - :doc:`RTC LED Blink <drivers/rtc_led_blink>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`
      - :doc:`Sciclient CCS Init <drivers/sciclient_ccs_init>`

   **SPINLOCK**
      - :doc:`Spinlock Example <drivers/spinlock_example>`

   **TISP**
      - :doc:`TISP 2D FFT DSP Offload <tisp/fft2d_rtos_dsp_offload>`
      - :doc:`TISP Real-Time Signal Chain Examples <tisp/sigchain_dsp_rt/sigchain_top>`
      - :doc:`Cascade Biquad Parametric EQ <tisp/sigchain_dsp_rt/sigchain_biquad_cascade>`
      - :doc:`EQ, Gain, and Mute <tisp/sigchain_dsp_rt/sigchain_eq_gain_mute>`
      - :doc:`Router with FFT/IFFT DSP Processing (8ch to 12ch) <tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch>`
      - :doc:`Comprehensive Audio Chain (8ch to 12ch) <tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo DMA <drivers/uart_echo_dma>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **WATCHDOG**
      - :doc:`Watchdog interrupt mode <drivers/watchdog_interrupt_mode>`

.. only:: SOC_AM62PX

   **DDR**
      - :doc:`DDR ECC Test MAIN ESM <drivers/ddr_ecc_test_main_esm>`
      - :doc:`DDR PERF Test <drivers/ddr_perf>`

   **DSS**
      - :doc:`DSS Colorbar Test <drivers/dss_colorbar_test>`
      - :doc:`DSS Display Share <drivers/dss_display_share>`
      - :doc:`DSS Display Test <drivers/dss_display_test>`
      - :doc:`DSS Safety Test <drivers/dss_safety_test>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC RP Message Linux Echo <drivers/ipc_rpmessage_linux_echo>`
      - :doc:`IPC RP Message QNX Echo <drivers/ipc_rpmessage_qnx_echo>`

   **MCASP**
      - :doc:`MCASP Early Chime <drivers/mcasp_early_chime>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`

   **OSPI**
      - :doc:`OSPI Flash Diagnostic <drivers/ospi_flash_diag>`
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`
      - :doc:`OSPI PHY Grapher UART <drivers/ospi_phy_grapher_uart>`

   **PMIC**
      - :doc:`PMIC Q&A watchdog interrupt example <drivers/pmic_qa_watchdog_interrupt>`
      - :doc:`PMIC Q&A watchdog reset example <drivers/pmic_qa_watchdog_reset>`
      - :doc:`PMIC trigger watchdog interrupt example <drivers/pmic_trigger_watchdog_interrupt>`
      - :doc:`PMIC trigger watchdog reset example <drivers/pmic_trigger_watchdog_reset>`
      - :doc:`PMIC user register configuration example <drivers/pmic_user_reg_cfg>`

   **PMU**
      - :doc:`PMU Multievent <drivers/pmu_multievent>`

   **RTC**
      - :doc:`RTC LED Blink <drivers/rtc_led_blink>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

.. only:: SOC_AM62LX

   **ADC**
      - :doc:`ADC Singleshot <drivers/adc_singleshot>`

   **DSS**
      - :doc:`DSS Colorbar Test <drivers/dss_colorbar_test>`
      - :doc:`DSS Display Test <drivers/dss_display_test>`
      - :doc:`DSS Safety Test <drivers/dss_safety_test>`
      - :doc:`DSS Splash Demo <drivers/dss_splash_demo>`

   **ECAP**
      - :doc:`ECAP APWM mode <drivers/ecap_apwm_mode>`
      - :doc:`ECAP EPWM Loopback <drivers/ecap_epwm_loopback>`

   **EPWM**
      - :doc:`EPWM Duty Cycle <drivers/epwm_duty_cycle>`
      - :doc:`EPWM Duty Cycle Sync <drivers/epwm_duty_cycle_sync>`

   **EQEP**
      - :doc:`EQEP Capture <drivers/eqep_capture>`
      - :doc:`EQEP frequency measurement <drivers/eqep_frequency_measurement>`
      - :doc:`EQEP Position Speed <drivers/eqep_position_speed>`

   **GPIO**
      - :doc:`GPIO Input Interrupt <drivers/gpio_input_interrupt>`
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCASP**
      - :doc:`MCASP Loopback <drivers/mcasp_loopback>`
      - :doc:`MCASP Playback <drivers/mcasp_playback_codec_aic31>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`
      - :doc:`MCSPI Loopback DMA <drivers/mcspi_loopback_dma>`
      - :doc:`MCSPI Performance 8-Bit <drivers/mcspi_performance_8bit>`
      - :doc:`MCSPI Performance 32-Bit <drivers/mcspi_performance_32bit>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`
      - :doc:`MMCSD FILE IO <drivers/mmcsd_file_io>`

   **OSPI**
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`
      - :doc:`OSPI Flash Diagnostic <drivers/ospi_flash_diag>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo BCDMA <drivers/uart_echo_bcdma>`
      - :doc:`UART Echo DMA <drivers/uart_echo_dma>`
      - :doc:`UART Echo DMA Multi-Instance <drivers/uart_echo_dma_multi_instance>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA SW Trigger <drivers/udma_sw_trigger>`

   **WATCHDOG**
      - :doc:`Watchdog interrupt mode <drivers/watchdog_interrupt_mode>`

.. only:: SOC_J722S

   **CSIRX**
      - :doc:`CSIRX CAPTURE TEST <drivers/csirx_capture_test>`

   **DSS**
      - :doc:`DSS Display Test <drivers/dss_display_test>`

   **GPIO**
      - :doc:`GPIO LED Blink <drivers/gpio_led_blink>`

   **I2C**
      - :doc:`I2C Led Blink <drivers/i2c_led_blink>`
      - :doc:`I2C Read <drivers/i2c_read>`
      - :doc:`I2C Temperature Read <drivers/i2c_temperature>`

   **DDR**
      - :doc:`DDR PERF Test <drivers/ddr_perf>`

   **IPC**
      - :doc:`IPC Notify Echo <drivers/ipc_notify_echo>`
      - :doc:`IPC RP Message Echo <drivers/ipc_rpmessage_echo>`
      - :doc:`IPC RP Message Linux Echo <drivers/ipc_rpmessage_linux_echo>`
      - :doc:`IPC RP Message QNX Echo <drivers/ipc_rpmessage_qnx_echo>`

   **MCAN**
      - :doc:`MCAN Loopback Interrupt <drivers/mcan_loopback_interrupt>`
      - :doc:`MCAN Loopback Polling <drivers/mcan_loopback_polling>`

   **MCSPI**
      - :doc:`MCSPI Loopback <drivers/mcspi_loopback>`

   **MMCSD**
      - :doc:`MMCSD RAW IO <drivers/mmcsd_raw_io>`

   **OSPI**
      - :doc:`OSPI Flash IO <drivers/ospi_flash_io>`

   **SCICLIENT**
      - :doc:`Sciclient Get Version <drivers/sciclient_get_version>`

   **UART**
      - :doc:`UART Echo <drivers/uart_echo>`
      - :doc:`UART Echo Callback <drivers/uart_echo_callback>`
      - :doc:`UART Echo Low Latency Interrupt <drivers/uart_echo_low_latency_interrupt>`
      - :doc:`UART Echo Low Latency Polling <drivers/uart_echo_low_latency_polling>`

   **UDMA**
      - :doc:`UDMA Memcpy Interrupt <drivers/udma_memcpy_interrupt>`
      - :doc:`UDMA Memcpy Polling <drivers/udma_memcpy_polling>`
      - :doc:`UDMA Chaining <drivers/udma_chaining>`
