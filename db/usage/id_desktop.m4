dnl
dnl Generic desktop controls usage page IDs.
dnl
dnl Copyright (C) 2010 Nikolai Kondrashov
dnl
dnl This file is part of hidrd.
dnl
dnl Hidrd is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl Hidrd is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with hidrd; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
dnl
dnl
dnl ID - describe a delegated usage ID.
dnl Arguments:
dnl     * Hexadecimal usage ID (four digits, uppercase)
dnl     * ID token (non-capitalized, underscores for spaces)
dnl     * Usage types (comma separated, case as per specification)
dnl     * ID description (non-capitalized)
dnl
ID(`0001',  `pointer',                  `CP',       `pointer')dnl
ID(`0002',  `mouse',                    `CA',       `mouse')dnl
ID(`0004',  `joystick',                 `CA',       `joystick')dnl
ID(`0005',  `gamepad',                  `CA',       `gamepad')dnl
ID(`0006',  `keyboard',                 `CA',       `keyboard')dnl
ID(`0007',  `keypad',                   `CA',       `keypad')dnl
ID(`0008',  `multi_axis_ctrl',          `CA',       `multi-axis controller')dnl
ID(`0009',  `tablet_PC_system',         `CA',       `tablet PC system controls')dnl
ID(`0030',  `X',                        `DV',       `X')dnl
ID(`0031',  `Y',                        `DV',       `Y')dnl
ID(`0032',  `Z',                        `DV',       `Z')dnl
ID(`0033',  `Rx',                       `DV',       `Rx')dnl
ID(`0034',  `Ry',                       `DV',       `Ry')dnl
ID(`0035',  `Rz',                       `DV',       `Rz')dnl
ID(`0036',  `slider',                   `DV',       `slider')dnl
ID(`0037',  `dial',                     `DV',       `dial')dnl
ID(`0038',  `wheel',                    `DV',       `wheel')dnl
ID(`0039',  `hat_switch',               `DV',       `hat switch')dnl
ID(`003A',  `counted_buffer',           `CL',       `counted buffer')dnl
ID(`003B',  `byte_count',               `DV',       `byte count')dnl
ID(`003C',  `motion_wakeup',            `OSC',      `motion wakeup')dnl
ID(`003D',  `start',                    `OOC',      `start')dnl
ID(`003E',  `select',                   `OOC',      `select')dnl
ID(`0040',  `Vx',                       `DV',       `Vx')dnl
ID(`0041',  `Vy',                       `DV',       `Vy')dnl
ID(`0042',  `Vz',                       `DV',       `Vz')dnl
ID(`0043',  `Vbrx',                     `DV',       `Vbrx')dnl
ID(`0044',  `Vbry',                     `DV',       `Vbry')dnl
ID(`0045',  `Vbrz',                     `DV',       `Vbrz')dnl
ID(`0046',  `Vno',                      `DV',       `Vno')dnl
ID(`0047',  `feature_notification',     `DV,DF',    `feature notification')dnl
ID(`0048',  `resolution_multiplier',    `DV',       `resolution multiplier')dnl
ID(`0080',  `sys_control',              `CA',       `system control')dnl
ID(`0081',  `sys_power_down',           `OSC',      `system power down')dnl
ID(`0082',  `sys_sleep',                `OSC',      `system sleep')dnl
ID(`0083',  `sys_wake_up',              `OSC',      `system wake up')dnl
ID(`0084',  `sys_context_menu',         `OSC',      `system context menu')dnl
ID(`0085',  `sys_main_menu',            `OSC',      `system main menu')dnl
ID(`0086',  `sys_app_menu',             `OSC',      `system app menu')dnl
ID(`0087',  `sys_menu_help',            `OSC',      `system menu help')dnl
ID(`0088',  `sys_menu_exit',            `OSC',      `system menu exit')dnl
ID(`0089',  `sys_menu_select',          `OSC',      `system menu select')dnl
ID(`008A',  `sys_menu_right',           `RTC',      `system menu right')dnl
ID(`008B',  `sys_menu_left',            `RTC',      `system menu left')dnl
ID(`008C',  `sys_menu_up',              `RTC',      `system menu up')dnl
ID(`008D',  `sys_menu_down',            `RTC',      `system menu down')dnl
ID(`008E',  `sys_cold_restart',         `OSC',      `system cold restart')dnl
ID(`008F',  `sys_warm_restart',         `OSC',      `system warm restart')dnl
ID(`0090',  `D_pad_up',                 `OOC',      `D-pad up')dnl
ID(`0091',  `D_pad_down',               `OOC',      `D-pad down')dnl
ID(`0092',  `D_pad_right',              `OOC',      `D-pad right')dnl
ID(`0093',  `D_pad_left',               `OOC',      `D-pad left')dnl
ID(`00A0',  `sys_dock',                 `OSC',      `system dock')dnl
ID(`00A1',  `sys_undock',               `OSC',      `system undock')dnl
ID(`00A2',  `sys_setup',                `OSC',      `system setup')dnl
ID(`00A3',  `sys_break',                `OSC',      `system break')dnl
ID(`00A4',  `sys_dbgr_break',           `OSC',      `system debugger break')dnl
ID(`00A5',  `app_break',                `OSC',      `application break')dnl
ID(`00A6',  `app_dbgr_break',           `OSC',      `application debugger break')dnl
ID(`00A7',  `sys_speaker_mute',         `OSC',      `system speaker mute')dnl
ID(`00A8',  `sys_hibernate',            `OSC',      `system hibernate')dnl
ID(`00B0',  `sys_dspl_invert',          `OSC',      `system display invert')dnl
ID(`00B1',  `sys_dspl_internal',        `OSC',      `system display internal')dnl
ID(`00B2',  `sys_dspl_external',        `OSC',      `system display external')dnl
ID(`00B3',  `sys_dspl_both',            `OSC',      `system display both')dnl
ID(`00B4',  `sys_dspl_dual',            `OSC',      `system display dual')dnl
ID(`00B5',  `sys_dspl_toggle_int_ext',  `OSC',      `system display toggle int/ext')dnl
ID(`00B6',  `sys_dspl_swap_1_2',        `OSC',      `system display swap primary/secondary')dnl
ID(`00B7',  `sys_dspl_LCD_autoscale',   `OSC',      `system display LCD autoscale')dnl
ID(`00C9',  `sys_dspl_rot_lock_btn',    `OOC',      `system display rotation lock button')dnl
ID(`00CA',  `sys_dspl_rot_lock_sld',    `OOC',      `system display rotation lock slider switch')dnl
