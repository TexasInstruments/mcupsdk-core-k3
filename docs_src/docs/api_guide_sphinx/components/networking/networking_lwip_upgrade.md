# Upgrade

```{contents}
:depth: 2
:local:
```

## Upgrade to version 2.2.1

In MCU+ SDK release version 11.02.00, LwIP stack has been upgraded to support LwIP version 2.2.1 (tag: `STABLE-2_2_1_RELEASE`).
Below is the [official release news](https://savannah.nongnu.org/news/?group=lwip) from LwIP-
> lwIP 2.2.1 is now available from the lwIP download area
> or via git (using the STABLE-2_2_1_RELEASE tag) or via the gitweb link.<br>
> This is mostly a bugfix release, summing up all fixes of the last 1.5 years.

:::{only} SOC_AM62DX
   Following are the changes done in MCU+ SDK during upgrade -
   1. The `mqtt.c` file in `${SDK_INSTALL_PATH}/examples/lwip/cpsw_lwip_mqtt` has been updated to accommodate changes to the `mqtt_connect_client_info_t` struct introduced in the new stack version.
:::

This is a smaller bugfix-only release. Contrib has not been changed since 2.1.0.
For a list of the bugs fixed, see `${SDK_INSTALL_PATH}/source/networking/lwip/lwip-stack/CHANGELOG`.

## Upgrade to version 2.2.0

In MCU+ SDK release version 09.01.00, LwIP stack is upgraded to support LwIP version 2.2.0 LwIP (tag: `STABLE-2_2_0_RELEASE`). Below is the official release news from LwIP-
> lwIP 2.2.0 is now available from the lwIP download area
> or via git (using the STABLE-2_2_0_RELEASE tag) or via this gitweb link:
> There have been some bugs fixed, and some new features were added (most notably full ACD support).
> Additionally, the contents of the contrib repository has been moved to the main repository ('contrib' directory on top level) to make things more consistent, especially with git. The old contrib repository should not be used any more.
> The 2.1.x branch will not be continued, so eventually, all users of 2.1.x might want to upgrade to get bugfixes.

Following are the changes done in MCU+ SDK during upgrade -
1. Deleted `lwip-contrib` directory in `${SDK_INSTALL_PATH}/source/networking/lwip`.
2. In makefiles, all the references to `lwip-contrib` directory is replaced with new `contrib` directory present in `${SDK_INSTALL_PATH}/source/networking/lwip-stack/contrib`.
3. Added `acd.c` (newly added file in stack) of lwip stack library makefile
4. All the references to file `tftp_server.c` is replaced with `tftp.c`. `tftp_server.c` file is renamed in latest lwip stack, and has functionality of both tftp server and client.
5. No change to pre-compiled `lwip-contrib` library status. It is pre-compiled now using new location for `contrib` directory and continue to exists.

If you have a custom makefile used to compile lwip stack, please ensure to make the above changes to use new version of LwIP stack.
