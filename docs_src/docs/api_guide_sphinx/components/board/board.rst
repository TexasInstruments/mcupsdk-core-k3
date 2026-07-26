Board Peripheral Drivers
==========================

.. toctree::
   :maxdepth: 1
   :titlesonly:
   :hidden:

   flash
   led
   hyperram
   panel
   eeprom
   pmic
   ioexp_tca6424

This module has information related to the different board level peripherals that are supported.

It consists of below sub-modules

.. only:: SOC_AM64X or SOC_AM243X or SOC_AM263X

   - :doc:`Flash <flash>`
   - :doc:`EEPROM <eeprom>`
   - :doc:`LED <led>`

.. only:: SOC_AM62PX or SOC_AM62DX

   - :doc:`Flash <flash>`
   - :doc:`EEPROM <eeprom>`
   - :doc:`LED <led>`
   - :doc:`PANEL <panel>`
   - :doc:`PMIC <pmic>`

.. only:: SOC_AM62X

   - :doc:`Flash <flash>`
   - :doc:`LED <led>`
   - :doc:`PANEL <panel>`

.. only:: SOC_AM62AX

   - :doc:`Flash <flash>`
   - :doc:`EEPROM <eeprom>`
   - :doc:`LED <led>`

.. only:: SOC_AM275X

   - :doc:`Flash <flash>`
   - :doc:`EEPROM <eeprom>`
   - :doc:`LED <led>`
   - :doc:`HyperRam <hyperram>`
   - :doc:`PMIC <pmic>`
   - :doc:`IO Expander TCA6424 <ioexp_tca6424>`

.. only:: SOC_AM62LX

   - :doc:`Flash <flash>`
   - :doc:`LED <led>`
   - :doc:`PANEL <panel>`
