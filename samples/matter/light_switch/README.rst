.. _matter_light_switch_sample:
.. _chip_light_switch_sample:

Matter: Light switch
####################

.. contents::
   :local:
   :depth: 2

This light switch sample demonstrates the usage of the :ref:`Matter <ug_matter>` application layer to build a switch device that binds with lighting devices and changes the state of their LEDs.
You can use this sample as a reference for creating your own application.

When configured together with the :ref:`Matter light bulb <matter_light_bulb_sample>` sample (or other lighting sample) and when using a Matter controller, the light switch can control one light bulb directly or a group of light bulbs remotely over a Matter network built on top of a low-power, 802.15.4 Thread, or on top of a Wi-Fi® network.
Support for both Thread and Wi-Fi is mutually exclusive and depends on the hardware platform, so only one protocol can be supported for a specific light switch device.
Depending on the network you choose:

* In case of Thread, this device works as a Thread :ref:`Sleepy End Device <thread_ot_device_types>`.
* In case of Wi-Fi, this device works in the :ref:`Legacy Power Save mode <ug_nrf70_developing_powersave_dtim_unicast>`.
  This means that the device sleeps most of the time and wakes up on each Delivery Traffic Indication Message (DTIM) interval to poll for pending messages.

Requirements
************

The sample supports the following development kits:

.. table-from-sample-yaml::

For this sample to work, you also need at least one :ref:`Matter light bulb <matter_light_bulb_sample>` sample programmed to another supported development kit.

To commission the device and run all required commands, you need also a :ref:`Matter controller <ug_matter_configuring_controller>`.
By default, this sample is configured to use the CHIP Tool as Matter controller.
See the :doc:`matter:chip_tool_guide` page in the Matter documentation for the CHIP Tool's setup information.

If you decide to use :ref:`matter_light_switch_sample_ui_matter_cli`, you also need a USB cable for the serial connection.

.. note::
    |matter_gn_required_note|


IPv6 network support
====================

The development kits for this sample offer the following IPv6 network support for Matter:

* Matter over Thread is supported for ``nrf52840dk/nrf52840``, ``nrf5340dk/nrf5340/cpuapp``, ``nrf21540dk/nrf52840``, and ``nrf54l15dk/nrf54l15/cpuapp``.
* Matter over Wi-Fi is supported for ``nrf5340dk/nrf5340/cpuapp`` with the ``nrf7002ek`` shield attached or for ``nrf7002dk/nrf5340/cpuapp``.

Overview
********

The sample controls the state of the state-indication LED on connected light bulbs devices.
After configuring the light switch sample, the lighting devices get proper `Access Control List`_ from the Matter controller to start receiving commands sent from the light switch.
Then, the light switch device prepares a new binding table to be able to discover light bulb devices and perform :ref:`matter_light_switch_sample_binding`.

After the binding is complete, the application can control the state of the connected lighting devices in one of the following ways:

* With a single light bulb, it uses a Certificate-Authenticated Session Establishment session (CASE session) for direct communication with the single light bulb.
* With a group of light bulbs, it uses multicast messages sent through the IPv6 network using :ref:`matter_light_switch_sample_groupcast` with all light bulbs in the group.

.. _matter_light_switch_sample_acl:

Access Control List
===================

The Access Control List (ACL) is a list related to the Access Control cluster.
The list contains rules for managing and enforcing access control for a node's endpoints and their associated cluster instances.
In this sample's case, this allows the lighting devices to receive messages from the light switch and run them.

You can read more about ACLs on the :doc:`matter:access-control-guide` in the Matter documentation.

.. _matter_light_switch_sample_groupcast:

Group communication
===================

Group communication (groupcast or multicast) refers to messages and commands sent to the address of a group that includes multiple devices with the same Groups cluster.
The cluster manages the content of a node-wide Group Table that is part of the underlying interaction layer.
This is done on per endpoint basis.
After creating the Group cluster with specific ``ID`` and ``Name``, a device gets its own IPv6 multicast address and is ready to receive groupcast commands.

In this sample, the light switch device is able to create a groupcast message and send it to the chosen IPv6 multicast address.
This allows the light switch more than one lighting devices at the same time.

.. note::
   Writing the groupcast table on the devices blocks sending unicast commands.
   If you want to go back to the original state, perform factory reset of the device.

.. _matter_light_switch_sample_binding:

Binding
=======

.. matter_light_switch_sample_binding_start

Binding refers to establishing a relationship between endpoints on the local and remote nodes.
With binding, local endpoints are pointed and bound to the corresponding remote endpoints.
Both must belong to the same cluster type.
Binding lets the local endpoint know which endpoints are going to be the target for the client-generated actions on one or more remote nodes.

.. matter_light_switch_sample_binding_end

In this sample, the light switch controls one or more lighting devices, but does not know the remote endpoints of the lights (on remote nodes).
Using binding, the light switch device updates its Binding cluster with all relevant information about the lighting devices, such as their IPv6 address, node ID, and the IDs of the remote endpoints that contains the On/Off cluster and the LevelControl cluster, respectively.

Configuration
*************

|config|

.. _matter_light_switch_custom_configs:

Matter light switch custom configurations
=========================================

.. include:: ../light_bulb/README.rst
    :start-after: matter_light_bulb_sample_configuration_file_types_start
    :end-before: matter_light_bulb_sample_configuration_file_types_end

Matter light switch with Trusted Firmware-M
===========================================

.. include:: ../template/README.rst
    :start-after: matter_template_build_with_tfm_start
    :end-before: matter_template_build_with_tfm_end

.. _matter_light_switch_snippets:

Snippets
========

.. |snippet| replace:: :makevar:`light_switch_SNIPPET`

.. include:: /includes/sample_snippets.txt

The following snippet is available:

* ``lit_icd`` - Enables experimental LIT ICD support.

  .. |snippet_zap_file| replace:: :file:`snippets/lit_icd/light_switch.zap`
  .. |snippet_dir| replace:: :file:`snippets/lit_icd`

  .. include:: /includes/matter_snippets_note.txt

.. |Bluetooth| replace:: Bluetooth®

.. include:: /includes/advanced_conf_matter.txt

.. _matter_light_switch_sample_ui:

User interface
**************

.. tabs::

   .. group-tab:: nRF52, nRF53 and nRF70 DKs

      LED 1:
         .. include:: /includes/matter_sample_state_led.txt

      LED 2:
         The LED starts blinking evenly (500 ms on/500 ms off) when the Identify command of the Identify cluster is received on the endpoint ``1``.
         The command's argument can be used to specify the duration of the effect.

      All LEDs:
         Blink in unison when the factory reset procedure is initiated.

      Button 1:
         .. include:: /includes/matter_sample_button.txt

      Button 2:
         Controls the light on the bound lighting device.
         Depending on how long you press the button:

         * If pressed for less than 0.5 seconds, it changes the light state to the opposite one on the bound lighting device (:ref:`light bulb <matter_light_bulb_sample>`).
         * If pressed for more than 0.5 seconds, it changes the brightness of the light on the bound lighting bulb device (:ref:`light bulb <matter_light_bulb_sample>`).
           The brightness is changing from 0% to 100% with 1% increments every 300 milliseconds as long as **Button 2** is pressed.

      Button 3:
         Functions as the User Active Mode Trigger (UAT) button.
         For more information about Intermittently Connected Devices (ICD) and User Active Mode Trigger, see the :ref:`ug_matter_device_low_power_icd` documentation section.

         .. note::
            To enable this functionality, :ref:`activate the lit_icd snippet <matter_light_switch_snippets>`.
            ICD and UAT functionality is currently supported only for Matter over Thread.

      .. include:: /includes/matter_segger_usb.txt

      NFC port with antenna attached:
         Optionally used for obtaining the `Onboarding information`_ from the Matter accessory device to start the :ref:`commissioning procedure <matter_light_switch_sample_remote_control_commissioning>`.

   .. group-tab:: nRF54 DKs

      LED 0:
         .. include:: /includes/matter_sample_state_led.txt

      LED 1:
         The LED starts blinking evenly (500 ms on/500 ms off) when the Identify command of the Identify cluster is received on the endpoint ``1``.
         The command's argument can be used to specify the duration of the effect.

      All LEDs:
         Blink in unison when the factory reset procedure is initiated.

      Button 0:
         .. include:: /includes/matter_sample_button.txt

      Button 1:
         Controls the light on the bound lighting device.
         Depending on how long you press the button:

         * If pressed for less than 0.5 seconds, it changes the light state to the opposite one on the bound lighting device (:ref:`light bulb <matter_light_bulb_sample>`).
         * If pressed for more than 0.5 seconds, it changes the brightness of the light on the bound lighting bulb device (:ref:`light bulb <matter_light_bulb_sample>`).
           The brightness is changing from 0% to 100% with 1% increments every 300 milliseconds as long as **Button 1** is pressed.

      Button 2:
         Functions as the User Active Mode Trigger (UAT) button.
         For more information about Intermittently Connected Devices (ICD) and User Active Mode Trigger, see the :ref:`ug_matter_device_low_power_icd` documentation section.

         .. note::
            To enable this functionality, :ref:`activate the lit_icd snippet <matter_light_switch_snippets>`.

      .. include:: /includes/matter_segger_usb.txt

      NFC port with antenna attached:
         Optionally used for obtaining the `Onboarding information`_ from the Matter accessory device to start the :ref:`commissioning procedure <matter_light_switch_sample_remote_control_commissioning>`.

.. _matter_light_switch_sample_ui_matter_cli:

Matter CLI commands
===================

If you build the application with the :ref:`debug configuration <matter_light_switch_custom_configs>`, you can use a series of commands to control the light switch device.
These commands can be sent to one device (unicast) or a group of devices (groupcast).

Unicast commands
----------------

You can use the following commands for direct communication with the single lighting device:

switch onoff on
   This command turns on the state-indication LED on the bound lighting device.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch onoff on

switch onoff off
   This command turns off the state-indication LED on the bound lighting device.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch onoff off

switch onoff toggle
   This command changes the state of the state-indication LED to the opposite state on the bound lighting device.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch onoff toggle

Groupcast commands
------------------

You can use the following commands a group of devices that are programmed with the Light Switch Example application by using the Matter CLI:

switch groups onoff on
   This command turns on the state-indication LED on each bound lighting device connected to the same group.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch groups onoff on

switch groups onoff off
   This command turns off the state-indication LED on each bound lighting device connected to the same group.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch groups onoff off

switch groups onoff toggle
   This command changes the state of the state-indication LED to the opposite state on each bound lighting device connected to the same group.
   For example:

   .. parsed-literal::
      :class: highlight

      uart:~$ matter switch groups onoff toggle

Building and running
********************

.. |sample path| replace:: :file:`samples/matter/light_switch`

.. include:: /includes/build_and_run.txt

.. |sample_or_app| replace:: sample
.. |ipc_radio_dir| replace:: :file:`sysbuild/ipc_radio`

.. include:: /includes/ipc_radio_conf.txt

See `Configuration`_ for information about building the sample with the DFU support.

Selecting a configuration
=========================

Before you start testing the application, you can select one of the :ref:`matter_light_switch_custom_configs`.
See :ref:`app_build_file_suffixes` and :ref:`cmake_options` for more information how to select a configuration.

Testing
*******

After building the sample and programming it to your development kit, complete the steps in the following sections.

.. _matter_light_switch_sample_prepare_for_testing:

Prepare for testing
===================

After building this and the :ref:`Matter Light Bulb <matter_light_bulb_sample>` samples, and programming them to the development kits, complete the following steps:

.. note::
   In both samples (light switch and light bulb), a Bluetooth LE discriminator is set with the same value by default (hexadecimal: ``0xF00``; decimal: ``3840``).
   This means that only one uncommissioned device can be powered up before commissioning.
   If both are powered up at the same time, the CHIP Tool can commission a random device and the node ID assignment is also random.
   When one device is commissioned, power up the next device and perform the commissioning.

   To avoid this unclear situation, you can set up your unique discriminator in the :file:`src/chip_project_config.h` file by changing the :kconfig:option:`CHIP_DEVICE_CONFIG_USE_TEST_SETUP_DISCRIMINATOR` value.
   Then build an example and commission with your unique discriminator.

.. matter_light_switch_sample_prepare_to_testing_start

1. |connect_kit|
#. |connect_terminal_ANSI|
#. If the devices were not erased during the programming, press and hold **Button 1** (**Button 0** for nRF54 Series device kits) on each device until the factory reset takes place.
#. On each device, press **Button 1** (**Button 0** for nRF54 Series device kits) to start the Bluetooth LE advertising.
#. Commission the devices to the Matter network.
   See `Commissioning the device`_ for more information.

   During the commissioning process, write down the values for the light switch node ID and the light bulb node ID (or IDs, if you are using more than one light bulb).
   These IDs are used in the next steps (*<light_switch_node_ID>* and *<light_bulb_node_ID>*, respectively).
#. Use the :doc:`CHIP Tool <matter:chip_tool_guide>` ("Writing ACL to the ``accesscontrol`` cluster" section) to add proper ACL for the light bulb devices, establish a group for groupcast and bind the light switch.
   Depending on the number of the light bulb devices you are using, use one of the following commands, with *<light_switch_node_ID>* and *<light_bulb_node_ID>* values from the previous step about commissioning.

   If you are using only one light bulb device, follow the instructions in the **unicast** tab to bind the light switch with the light bulb device.
   If you are using more than one light bulb device, follow the instructions in the **groupcast** tab to connect all devices to the multicast group

   .. tabs::

      .. group-tab:: unicast

         The unicast binding is used to bind the light switch with only one light bulb device.
         Run the following commands to bind the light switch with the light bulb device:

         1. Write ACL to the ``accesscontrol`` cluster:

            .. parsed-literal::
               :class: highlight

               chip-tool accesscontrol write acl '[{"fabricIndex": 1, "privilege": 5, "authMode": 2, "subjects": [112233], "targets": null}, {"fabricIndex": 1, "privilege": 3, "authMode": 2, "subjects": [<light_switch_node_ID>], "targets": [{"cluster": 6, "endpoint": 1, "deviceType": null}, {"cluster": 8, "endpoint": 1, "deviceType": null}]}]' <light_bulb_node_ID> 0

         #. Write a binding table to the light switch to inform the device about all endpoints by running this command (only for light switch):

            .. parsed-literal::
               :class: highlight

               chip-tool binding write binding '[{"fabricIndex": 1, "node": <light bulb node id>, "endpoint": 1, "cluster": 6}, {"fabricIndex": 1, "node": <light bulb node id>, "endpoint": 1, "cluster": 8}]' <light switch node id> 1


      .. group-tab:: groupcast

         The groupcast binding is used to bind the light switch with multiple light bulb devices.
         The following example shows how to estabilish a new group communication with the following parameters:

            * Group ID: 258
            * Group Name: Test_Group
            * Group Key Set ID: 349
            * Group Key Set Security Policy: 0
            * Epoch Key 0: a0a1a2a3a4a5a6a7a8a9aaabacad7531
            * Epoch Start Time 0: 1110000
            * Epoch Key 1: b0b1b2b3b4b5b6b7b8b9babbbcbd7531
            * Epoch Start Time 1: 1110001
            * Epoch Key 2: c0c1c2c3c4c5c6c7c8c9cacbcccd7531
            * Epoch Start Time 2: 1110002

         To learn more about groups in Matter, see the :ref:`ug_matter_group_communication` user guide.

         Run the following commands to bind the light switch with all light bulb devices:

         1. Set up a new group in the doc:`CHIP Tool <matter:chip_tool_guide>`:

            .. parsed-literal::
               :class: highlight

               chip-tool groupsettings add-keysets 349 0 2220000 hex:a0a1a2a3a4a5a6a7a8a9aaabacad7531
               chip-tool groupsettings bind-keyset 258 349


         #. Set up all light bulb devices:

            .. parsed-literal::
               :class: highlight

               chip-tool groupkeymanagement key-set-write {"groupKeySetID": 349, "groupKeySecurityPolicy": 0, "epochKey0": "a0a1a2a3a4a5a6a7a8a9aaabacad7531", "epochStartTime0": 1110000, "epochKey1": "b0b1b2b3b4b5b6b7b8b9babbbcbd7531", "epochStartTime1": 1110001, "epochKey2": "c0c1c2c3c4c5c6c7c8c9cacbcccd7531", "epochStartTime2": 1110002} <light bulb node id> 0
               chip-tool groupkeymanagement write group-key-map [{"groupId": 258, "groupKeySetID": 349, "fabricIndex": 1}] <light bulb node id> 0
               chip-tool groups add-group 258 Test_Group <light bulb node id> 1

               chip-tool accesscontrol write acl '[{"fabricIndex": 1, "privilege": 5, "authMode": 2, "subjects": [112233], "targets": null}, {"fabricIndex": 1, "privilege": 3, "authMode": 3, "subjects": [258], "targets": [{"cluster": null, "endpoint": 1, "deviceType": null}]}]' <light bulb node id> 0

         #. Set up the light switch device:

            .. parsed-literal::
               :class: highlight

               chip-tool groupkeymanagement key-set-write {"groupKeySetID": 349, "groupKeySecurityPolicy": 0, "epochKey0": "a0a1a2a3a4a5a6a7a8a9aaabacad7531", "epochStartTime0": 1110000, "epochKey1": "b0b1b2b3b4b5b6b7b8b9babbbcbd7531", "epochStartTime1": 1110001, "epochKey2": "c0c1c2c3c4c5c6c7c8c9cacbcccd7531", "epochStartTime2": 1110002} <light_switch_node_ID> 0
               chip-tool groupkeymanagement write group-key-map [{"groupId": 258, "groupKeySetID": 349, "fabricIndex": 1}] <light_switch_node_ID> 0
               chip-tool accesscontrol write acl [{"fabricIndex": 1, "privilege": 5, "authMode": 2, "subjects": [112233], "targets": null}, {"fabricIndex": 1, "privilege": 3, "authMode": 3, "subjects": [258], "targets": null}] <light_switch_node_ID> 0
               chip-tool binding write binding [{"fabricIndex": 1, "group": 258}] <light_switch_node_ID> 1

.. matter_light_switch_sample_prepare_to_testing_end

All devices are now bound and ready for testing communication.

.. note::

   In this sample, the ACL cluster is inserted into the light bulb's endpoint ``0``, and the Binding cluster is inserted into the light switch's endpoint ``1``.

Testing with bound light bulbs devices
======================================

.. matter_light_switch_sample_testing_start

After preparing devices for testing, you can test the communication of either a single light bulb or of a group of light bulbs with the light switch (but not both a single device and a group at the same time).

Complete the following steps using the light switch device:

.. tabs::

   .. group-tab:: nRF52, nRF53 and nRF70 DKs

      1. On the light switch device, use the :ref:`buttons <matter_light_switch_sample_ui>` to control the bound light bulbs:

         a. Press **Button 2** to turn off the state-indication LED located on the bound light bulb device.
         #. Press **Button 2** to turn the LED on again.
         #. Press **Button 2** and hold it for more than 0.5 seconds to test the dimmer functionality.

            The state-indication LED on the bound light bulb device changes its brightness from 0% to 100% with 1% increments every 300 milliseconds as long as **Button 2** is pressed.

      #. Using the terminal emulator connected to the light switch, run the following :ref:`Matter CLI commands <matter_light_switch_sample_ui_matter_cli>`:

         a. Write the following command to turn on state-indication LED located on the bound light bulb device:

            * For a single bound light bulb:

              .. parsed-literal::
                 :class: highlight

                 matter switch onoff on

            * For a group of light bulbs:

              .. parsed-literal::
                 :class: highlight

                 matter switch groups onoff on

         #. Write the following command to turn off the state-indication LED located on the bound light bulb device:

            * For a single bound light bulb:

              .. parsed-literal::
                 :class: highlight

                 matter switch onoff off

            * For a group of light bulbs:

              .. parsed-literal::
                 :class: highlight

                 matter switch groups onoff off

   .. group-tab:: nRF54 DKs

      1. On the light switch device, use the :ref:`buttons <matter_light_switch_sample_ui>` to control the bound light bulbs:

         #. Press **Button 1** to turn off the state-indication LED located on the bound light bulb device.
         #. Press **Button 1** to turn the LED on again.
         #. Press **Button 1** and hold it for more than 0.5 seconds to test the dimmer functionality.

            The state-indication LED on the bound light bulb device changes its brightness from 0% to 100% with 1% increments every 300 milliseconds as long as **Button 1** is pressed.

      #. Using the terminal emulator connected to the light switch, run the following :ref:`Matter CLI commands <matter_light_switch_sample_ui_matter_cli>`:

         a. Write the following command to turn on the state-indication LED located on the bound light bulb device:

            * For a single bound light bulb:

              .. parsed-literal::
                 :class: highlight

                 matter switch onoff on

            * For a group of light bulbs:

              .. parsed-literal::
                 :class: highlight

                 matter switch groups onoff on

         #. Write the following command to turn off the state-indication LED located on the bound light bulb device:

            * For a single bound light bulb:

              .. parsed-literal::
                 :class: highlight

                 matter switch onoff off

            * For a group of light bulbs:

              .. parsed-literal::
                 :class: highlight

                 matter switch groups onoff off

.. matter_light_switch_sample_testing_end

.. _matter_light_switch_sample_remote_control_commissioning:

Commissioning the device
========================

.. include:: ../lock/README.rst
    :start-after: matter_door_lock_sample_commissioning_start
    :end-before: matter_door_lock_sample_commissioning_end

Before starting the commissioning procedure, the device must be made discoverable over Bluetooth LE.
The device becomes discoverable automatically upon the device startup, but only for a predefined period of time (1 hour by default).
If the Bluetooth LE advertising times out, enable it again.

Onboarding information
----------------------

When you start the commissioning procedure, the controller must get the onboarding information from the Matter accessory device.
The onboarding information representation depends on your commissioner setup.

For this sample, you can use one of the following :ref:`onboarding information formats <ug_matter_network_topologies_commissioning_onboarding_formats>` to provide the commissioner with the data payload that includes the device discriminator and the setup PIN code:

  .. list-table:: Light switch sample onboarding information
     :header-rows: 1

     * - QR Code
       - QR Code Payload
       - Manual pairing code
     * - Scan the following QR code with the app for your ecosystem:

         .. figure:: ../../../doc/nrf/images/matter_qr_code_light_switch.png
            :width: 200px
            :alt: QR code for commissioning the light switch device

       - MT:4CT9142C00KA0648G00
       - 34970112332

.. include:: ../lock/README.rst
    :start-after: matter_door_lock_sample_onboarding_start
    :end-before: matter_door_lock_sample_onboarding_end

|matter_cd_info_note_for_samples|

Upgrading the device firmware
=============================

To upgrade the device firmware, complete the steps listed for the selected method in the :doc:`matter:nrfconnect_examples_software_update` tutorial in the Matter documentation.

Dependencies
************

This sample uses the Matter library that includes the |NCS| platform integration layer:

* `Matter`_

In addition, the sample uses the following |NCS| components:

* :ref:`dk_buttons_and_leds_readme`

The sample depends on the following Zephyr libraries:

* :ref:`zephyr:logging_api`
* :ref:`zephyr:kernel_api`
