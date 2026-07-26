Security
=========

.. toctree::
   :maxdepth: 1
   :hidden:
   :titlesonly:

   security/fwl_exception_log
   security/fwl_exception_trigger
   security/bootloader_test
   security/mcu_core_test_app
   security/tisci_msg
   security/runtime_debug_unlock
   security/crypto/sa3ul_aes_cbc_128
   security/crypto/sa3ul_aes_cbc_256
   security/crypto/sa3ul_aes_cmac_128
   security/crypto/sa3ul_aes_cmac_256
   security/crypto/sa3ul_aes_ecb_128
   security/crypto/sa3ul_aes_ecb_256
   security/crypto/sa3ul_hmac_sha1
   security/crypto/sa3ul_hmac_sha256
   security/crypto/sa3ul_hmac_sha256_multishot
   security/crypto/sa3ul_hmac_sha512
   security/crypto/sa3ul_rng
   security/crypto/sa3ul_sha

This page lists all the examples related to Security.

.. only:: SOC_AM62X or SOC_AM62AX or SOC_AM62DX

   **Firewall Examples**
      - :doc:`Firewall Exception Log Example <security/fwl_exception_log>`
      - :doc:`Firewall Exception Trigger Example <security/fwl_exception_trigger>`

.. only:: SOC_AM62AX

   **Bootloader and Core Examples**
      - :doc:`Bootloader Test Example <security/bootloader_test>`
      - :doc:`Mcu Core Test Application <security/mcu_core_test_app>`

.. only:: SOC_AM62AX or SOC_AM62DX

   **Cryptography Examples**
      - :doc:`SA3UL AES CBC-128 Test <security/crypto/sa3ul_aes_cbc_128>`
      - :doc:`SA3UL AES CBC-256 Test <security/crypto/sa3ul_aes_cbc_256>`
      - :doc:`SA3UL AES CMAC-128 Test <security/crypto/sa3ul_aes_cmac_128>`
      - :doc:`SA3UL AES CMAC-256 Test <security/crypto/sa3ul_aes_cmac_256>`
      - :doc:`SA3UL AES ECB-128 Test <security/crypto/sa3ul_aes_ecb_128>`
      - :doc:`SA3UL AES ECB-256 Test <security/crypto/sa3ul_aes_ecb_256>`
      - :doc:`SA3UL HMAC SHA-1 Test <security/crypto/sa3ul_hmac_sha1>`
      - :doc:`SA3UL HMAC SHA-256 Test <security/crypto/sa3ul_hmac_sha256>`
      - :doc:`SA3UL HMAC SHA-256 Multi shot Test <security/crypto/sa3ul_hmac_sha256_multishot>`
      - :doc:`SA3UL HMAC SHA-512 Test <security/crypto/sa3ul_hmac_sha512>`
      - :doc:`SA3UL Random Number Generator Test <security/crypto/sa3ul_rng>`
      - :doc:`SA3UL SHA Test <security/crypto/sa3ul_sha>`
      - :doc:`TISCI message example <security/tisci_msg>`
      - :doc:`Runtime debug unlock Example <security/runtime_debug_unlock>`

.. only:: SOC_AM62PX

   - :doc:`Firewall Exception Log Example <security/fwl_exception_log>`
   - :doc:`Firewall Exception Trigger Example <security/fwl_exception_trigger>`
   - :doc:`Bootloader Test Example <security/bootloader_test>`
   - :doc:`Mcu Core Test Application <security/mcu_core_test_app>`
   - :doc:`TISCI message example <security/tisci_msg>`
   - :doc:`Runtime debug unlock Example <security/runtime_debug_unlock>`

.. only:: SOC_AM275X

   **Other Security Examples**
      - :doc:`TISCI message example <security/tisci_msg>`
