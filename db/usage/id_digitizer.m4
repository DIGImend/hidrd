dnl
dnl Digitizer usage page IDs.
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
ID(`0001', `digitizer',                   `CA',   `digitizer')dnl
ID(`0002', `pen',                         `CA',   `pen')dnl
ID(`0003', `light_pen',                   `CA',   `light pen')dnl
ID(`0004', `touchscreen',                 `CA',   `touch screen')dnl
ID(`0005', `touchpad',                    `CA',   `touch pad')dnl
ID(`0006', `whiteboard',                  `CA',   `white board')dnl
ID(`0007', `coord_measuring_machine',     `CA',   `coordinate measuring machine')dnl
ID(`0008', `3D_digitizer',                `CA',   `3D digitizer')dnl
ID(`0009', `stereo_plotter',              `CA',   `stereo plotter')dnl
ID(`000A', `articulated_arm',             `CA',   `articulated arm')dnl
ID(`000B', `armature',                    `CA',   `armature')dnl
ID(`000C', `multipoint_digitizer',        `CA',   `multiple point digitizer')dnl
ID(`000D', `free_space_wand',             `CA',   `free space wand')dnl
ID(`000E', `configuration',               `CA',   `configuration')dnl
ID(`0020', `stylus',                      `CL',   `stylus')dnl
ID(`0021', `puck',                        `CL',   `puck')dnl
ID(`0022', `finger',                      `CL',   `finger')dnl
ID(`0023', `device_settings',             `CL',   `device settings')dnl
ID(`0030', `tip_pressure',                `DV',   `tip pressure')dnl
ID(`0031', `barrel_pressure',             `DV',   `barrel pressure')dnl
ID(`0032', `in_range',                    `MC',   `in range')dnl
ID(`0033', `touch',                       `MC',   `touch')dnl
ID(`0034', `untouch',                     `OSC',  `untouch')dnl
ID(`0035', `tap',                         `OSC',  `tap')dnl
ID(`0036', `quality',                     `DV',   `quality')dnl
ID(`0037', `data_valid',                  `MC',   `data valid')dnl
ID(`0038', `transducer_index',            `DV',   `transducer index')dnl
ID(`0039', `tablet_function_keys',        `CL',   `tablet function keys')dnl
ID(`003A', `program_change_keys',         `CL',   `program change keys')dnl
ID(`003B', `battery_strength',            `DV',   `battery strength')dnl
ID(`003C', `invert',                      `MC',   `invert')dnl
ID(`003D', `X_tilt',                      `DV',   `X tilt')dnl
ID(`003E', `Y_tilt',                      `DV',   `Y tilt')dnl
ID(`003F', `azimuth',                     `DV',   `azimuth')dnl
ID(`0040', `altitude',                    `DV',   `altitude')dnl
ID(`0041', `twist',                       `DV',   `twist')dnl
ID(`0042', `tip_switch',                  `MC',   `tip switch')dnl
ID(`0043', `secondary_tip_switch',        `MC',   `secondary tip switch')dnl
ID(`0044', `barrel_switch',               `MC',   `barrel switch')dnl
ID(`0045', `eraser',                      `MC',   `eraser')dnl
ID(`0046', `tablet_pick',                 `MC',   `tablet pick')dnl
ID(`0047', `touch_valid',                 `MC',   `touch valid')dnl
ID(`0048', `width',                       `DV',   `width')dnl
ID(`0049', `height',                      `DV',   `height')dnl
ID(`0051', `contact_identifier',          `DV',   `contact identifier')dnl
ID(`0052', `device_mode',                 `DV',   `device input mode')dnl
ID(`0053', `device_identifier',           `DV',   `device identifier')dnl
ID(`0054', `contact_count',               `DV',   `contact count')dnl
ID(`0055', `contact_count_maximum',       `SV',   `contact count maximum')dnl
ID(`0056', `scan_time',                   `DV',   `scan time')dnl
ID(`005A', `secondary_barrel_switch',     `MC',   `secondary barrel switch')dnl
ID(`005B', `transducer_serial_number',    `SV',   `transducer serial number')dnl
ID(`005C', `preferred_color',             `DV',   `preferred color')dnl
ID(`005D', `preferred_color_locked',      `MC',   `preferred color is locked')dnl
ID(`005E', `preferred_line_width',        `DV',   `preferred line width')dnl
ID(`005F', `preferred_line_width_locked', `MC',   `preferred line width is locked')dnl
ID(`0070', `preferred_line_style',        `NAry', `preferred line style')dnl
ID(`0071', `preferred_line_style_locked', `MC',   `preferred line style is locked')dnl
ID(`0072', `ink',                         `Sel',  `ink')dnl
ID(`0073', `pencil',                      `Sel',  `pencil')dnl
ID(`0074', `highlighter',                 `Sel',  `highlighter')dnl
ID(`0075', `chisel_marker',               `Sel',  `chisel marker')dnl
ID(`0076', `brush',                       `Sel',  `brush')dnl
ID(`0077', `no_preference',               `Sel',  `no preference')dnl
ID(`0080', `digitizer_diagnostic',        `CL',   `digitizer diagnostic')dnl
ID(`0081', `digitizer_error',             `NAry', `digitizer error')dnl
ID(`0082', `err_normal_status',           `Sel',  `err normal status')dnl
ID(`0083', `err_transducers_exceeded',    `Sel',  `err transducers exceeded')dnl
ID(`0084', `err_full_trans_ft_unavail',   `Sel',  `err full transducer features unavailable')dnl
ID(`0085', `err_charge_low',              `Sel',  `err charge low')dnl
ID(`0090', `transducer_software_info',    `CL',   `transducer software info')dnl
ID(`0091', `transducer_vendor_id',        `SV',   `transducer vendor id')dnl
ID(`0092', `transducer_product_id',       `SV',   `transducer product id')dnl
ID(`0093', `device_support_protos',       `NAry,CL', `device supported protocols')dnl
ID(`0094', `transducer_support_protos',   `NAry,CL', `transducer supported protocols')dnl
ID(`0095', `no_protocol',                 `Sel',  `no protocol')dnl
ID(`0096', `wacom_aes_protocol',          `Sel',  `wacom aes protocol')dnl
ID(`0097', `usi_protocol',                `Sel',  `usi protocol')dnl
ID(`00a0', `supported_report_rates',      `SV,CL', `supported report rates')dnl
ID(`00a1', `report_rate',                 `DV',   `report rate')dnl
ID(`00a2', `transducer_connected',        `SF',   `transducer connected')dnl
ID(`00a3', `switch_disabled',             `Sel',  `switch disabled')dnl
ID(`00a4', `switch_unimplemented',        `Sel',  `switch unimplemented')dnl
ID(`00a5', `transducer_switches',         `CL',   `transducer switches')dnl
