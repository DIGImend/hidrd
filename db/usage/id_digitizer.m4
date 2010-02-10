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
dnl     * ID token (lowercase, underscores as spaces)
dnl     * Usage types (comma separated, case as per specification)
dnl     * ID description (non-capitalized)
dnl
ID(`01', `digitizer',                   `CA',   `digitizer')dnl
ID(`02', `pen',                         `CA',   `pen')dnl
ID(`03', `light_pen',                   `CA',   `light pen')dnl
ID(`04', `touchscreen',                 `CA',   `touch screen')dnl
ID(`05', `touchpad',                    `CA',   `touch pad')dnl
ID(`06', `whiteboard',                  `CA',   `white board')dnl
ID(`07', `coord_measuring_machine',     `CA',   `coordinate measuring machine')dnl
ID(`08', `3d_digitizer',                `CA',   `3D digitizer')dnl
ID(`09', `stereo_plotter',              `CA',   `stereo plotter')dnl
ID(`0A', `articulated_arm',             `CA',   `articulated arm')dnl
ID(`0B', `armature',                    `CA',   `armature')dnl
ID(`0C', `multipoint_digitizer',        `CA',   `multiple point digitizer')dnl
ID(`0D', `free_space_wand',             `CA',   `free space wand')dnl
ID(`20', `stylus',                      `CL',   `stylus')dnl
ID(`21', `puck',                        `CL',   `puck')dnl
ID(`22', `finger',                      `CL',   `finger')dnl
ID(`30', `tip_pressure',                `DV',   `tip pressure')dnl
ID(`31', `barrel_pressure',             `DV',   `barrel pressure')dnl
ID(`32', `in_range',                    `MC',   `in range')dnl
ID(`33', `touch',                       `MC',   `touch')dnl
ID(`34', `untouch',                     `OSC',  `untouch')dnl
ID(`35', `tap',                         `OSC',  `tap')dnl
ID(`36', `quality',                     `DV',   `quality')dnl
ID(`37', `data_valid',                  `MC',   `data valid')dnl
ID(`38', `transducer_index',            `DV',   `transducer index')dnl
ID(`39', `tablet_function_keys',        `CL',   `tablet function keys')dnl
ID(`3A', `program_change_keys',         `CL',   `program change keys')dnl
ID(`3B', `battery_strength',            `DV',   `battery strength')dnl
ID(`3C', `invert',                      `MC',   `invert')dnl
ID(`3D', `x_tilt',                      `DV',   `x tilt')dnl
ID(`3E', `y_tilt',                      `DV',   `y tilt')dnl
ID(`3F', `azimuth',                     `DV',   `azimuth')dnl
ID(`40', `altitude',                    `DV',   `altitude')dnl
ID(`41', `twist',                       `DV',   `twist')dnl
ID(`42', `tip_switch',                  `MC',   `tip switch')dnl
ID(`43', `secondary_tip_switch',        `MC',   `secondary tip switch')dnl
ID(`44', `barrel_switch',               `MC',   `barrel switch')dnl
ID(`45', `eraser',                      `MC',   `eraser')dnl
ID(`46', `tablet_pick',                 `MC',   `tablet pick')dnl
