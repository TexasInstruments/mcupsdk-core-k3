# Fuison-1 daughtercard {#FUSION1_PAGE}

[TOC]

##Fusion daughter card

Fusion daughter card is adapter board to connect 4 camera sensors (IMX390+UB953 serializer)
through de-serializer (UB960) available on the Fusion1 daughter card to CSI2RX ports of |platform| SoC.

Connect the daughter card to "CSI2 Exp" connector.

.. figure:: images/fusion1_board.png

   Fusion1 Board

.. figure:: images/fusion1_board_camera.png

   Fusion1 Camera Setup

##Power-on sequence 

Since Fusion-1 board is powered from external supply, there is a power on sequence to be followed.

1)Power down both Fusion-1 and |platform| EVM
2)Connect Fusion-1 to |platform| EVM
3)Power on Fusion-1
4)Power on |platform| EVM

