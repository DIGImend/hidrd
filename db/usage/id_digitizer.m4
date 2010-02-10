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
ID(`01', `digitizer',                   `CA',   `Digitizer')dnl
ID(`02', `pen',                         `CA',   `Pen')dnl
ID(`03', `light_pen',                   `CA',   `Light pen')dnl
ID(`04', `touchscreen',                 `CA',   `Touch screen')dnl
ID(`05', `touchpad',                    `CA',   `Touch pad')dnl
ID(`06', `whiteboard',                  `CA',   `White board')dnl
ID(`07', `coord_measuring_machine',     `CA',   `Coordinate measuring machine')dnl
ID(`08', `3d_digitizer',                `CA',   `3D digitizer')dnl
ID(`09', `stereo_plotter',              `CA',   `Stereo plotter')dnl
ID(`0A', `articulated_arm',             `CA',   `Articulated arm')dnl
ID(`0B', `armature',                    `CA',   `Armature')dnl
ID(`0C', `multipoint_digitizer',        `CA',   `Multiple point digitizer')dnl
ID(`0D', `free_space_wand',             `CA',   `Free space wand')dnl
ID(`20', `stylus',                      `CL',   `Stylus')dnl
ID(`21', `puck',                        `CL',   `Puck')dnl
ID(`22', `finger',                      `CL',   `Finger')dnl
ID(`30', `tip_pressure',                `DV',   `Tip pressure')dnl
ID(`31', `barrel_pressure',             `DV',   `Barrel pressure')dnl
ID(`32', `in_range',                    `MC',   `In range')dnl
ID(`33', `touch',                       `MC',   `Touch')dnl
ID(`34', `untouch',                     `OSC',  `Untouch')dnl
ID(`35', `tap',                         `OSC',  `Tap')dnl
ID(`36', `quality',                     `DV',   `Quality')dnl
ID(`37', `data_valid',                  `MC',   `Data valid')dnl
ID(`38', `transducer_index',            `DV',   `Transducer index')dnl
ID(`39', `tablet_function_keys',        `CL',   `Tablet function keys')dnl
ID(`3A', `program_change_keys',         `CL',   `Program change keys')dnl
ID(`3B', `battery_strength',            `DV',   `Battery strength')dnl
ID(`3C', `invert',                      `MC',   `Invert')dnl
ID(`3D', `x_tilt',                      `DV',   `X tilt')dnl
ID(`3E', `y_tilt',                      `DV',   `Y tilt')dnl
ID(`3F', `azimuth',                     `DV',   `Azimuth')dnl
ID(`40', `altitude',                    `DV',   `Altitude')dnl
ID(`41', `twist',                       `DV',   `Twist')dnl
ID(`42', `tip_switch',                  `MC',   `Tip switch')dnl
ID(`43', `secondary_tip_switch',        `MC',   `Secondary tip switch')dnl
ID(`44', `barrel_switch',               `MC',   `Barrel switch')dnl
ID(`45', `eraser',                      `MC',   `Eraser')dnl
ID(`46', `tablet_pick',                 `MC',   `Tablet pick')dnl
