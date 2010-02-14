dnl
dnl Keyboard/keypad usage page IDs.
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
ID(`0000', `none',                           `Sel',   `no event')dnl
ID(`0001', `kb_error_rollover',              `Sel',   `keyboard ErrorRollOver')dnl
ID(`0002', `kb_post_fail',                   `Sel',   `keyboard POSTFail')dnl
ID(`0003', `kb_error_undefined',             `Sel',   `keyboard ErrorUndefined')dnl
ID(`0004', `kb_a',                           `Sel',   `keyboard a and A')dnl
ID(`0005', `kb_b',                           `Sel',   `keyboard b and B')dnl
ID(`0006', `kb_c',                           `Sel',   `keyboard c and C')dnl
ID(`0007', `kb_d',                           `Sel',   `keyboard d and D')dnl
ID(`0008', `kb_e',                           `Sel',   `keyboard e and E')dnl
ID(`0009', `kb_f',                           `Sel',   `keyboard f and F')dnl
ID(`000A', `kb_g',                           `Sel',   `keyboard g and G')dnl
ID(`000B', `kb_h',                           `Sel',   `keyboard h and H')dnl
ID(`000C', `kb_i',                           `Sel',   `keyboard i and I')dnl
ID(`000D', `kb_j',                           `Sel',   `keyboard j and J')dnl
ID(`000E', `kb_k',                           `Sel',   `keyboard k and K')dnl
ID(`000F', `kb_l',                           `Sel',   `keyboard l and L')dnl
ID(`0010', `kb_m',                           `Sel',   `keyboard m and M')dnl
ID(`0011', `kb_n',                           `Sel',   `keyboard n and N')dnl
ID(`0012', `kb_o',                           `Sel',   `keyboard o and O')dnl
ID(`0013', `kb_p',                           `Sel',   `keyboard p and P')dnl
ID(`0014', `kb_q',                           `Sel',   `keyboard q and Q')dnl
ID(`0015', `kb_r',                           `Sel',   `keyboard r and R')dnl
ID(`0016', `kb_s',                           `Sel',   `keyboard s and S')dnl
ID(`0017', `kb_t',                           `Sel',   `keyboard t and T')dnl
ID(`0018', `kb_u',                           `Sel',   `keyboard u and U')dnl
ID(`0019', `kb_v',                           `Sel',   `keyboard v and V')dnl
ID(`001A', `kb_w',                           `Sel',   `keyboard w and W')dnl
ID(`001B', `kb_x',                           `Sel',   `keyboard x and X')dnl
ID(`001C', `kb_y',                           `Sel',   `keyboard y and Y')dnl
ID(`001D', `kb_z',                           `Sel',   `keyboard z and Z')dnl
ID(`001E', `kb_1_and_exclam',                `Sel',   `keyboard 1 and !')dnl
ID(`001F', `kb_2_and_at',                    `Sel',   `keyboard 2 and @')dnl
ID(`0020', `kb_3_and_number',                `Sel',   `keyboard 3 and number')dnl
ID(`0021', `kb_4_and_dollar',                `Sel',   `keyboard 4 and $')dnl
ID(`0022', `kb_5_and_percent',               `Sel',   `keyboard 5 and %')dnl
ID(`0023', `kb_6_and_caret',                 `Sel',   `keyboard 6 and ^')dnl
ID(`0024', `kb_7_and_amp',                   `Sel',   `keyboard 7 and &')dnl
ID(`0025', `kb_8_and_star',                  `Sel',   `keyboard 8 and *')dnl
ID(`0026', `kb_9_and_left_paren',            `Sel',   ``keyboard 9 and ('')dnl
ID(`0027', `kb_0_and_right_paren',           `Sel',   ``keyboard 0 and )'')dnl
ID(`0028', `kb_enter',                       `Sel',   `keyboard Return (ENTER)')dnl
ID(`0029', `kb_escape',                      `Sel',   `keyboard Escape')dnl
ID(`002A', `kb_delete',                      `Sel',   `keyboard Delete (Backspace)')dnl
ID(`002B', `kb_tab',                         `Sel',   `keyboard Tab')dnl
ID(`002C', `kb_spacebar',                    `Sel',   `keyboard spacebar')dnl
ID(`002D', `kb_minus_and_underscore',        `Sel',   `keyboard - and _ (underscore)')dnl
ID(`002E', `kb_equals_and_plus',             `Sel',   `keyboard = and +')dnl
ID(`002F', `kb_lboxbracket_and_lbrace',      `Sel',   `keyboard [ and {')dnl
ID(`0030', `kb_rboxbracket_and_rbrace',      `Sel',   `keyboard ] and }')dnl
ID(`0031', `kb_backslash_and_pipe',          `Sel',   `keyboard backslash and |')dnl
ID(`0032', `kb_non_us_number_and_tilde',     `Sel',   `keyboard non-US number and ~')dnl
ID(`0033', `kb_semicolon_and_colon',         `Sel',   `keyboard ; and :')dnl
ID(`0034', `kb_quot_and_dblquot',            `Sel',   `keyboard ‘ and “')dnl
ID(`0035', `kb_grave_accent_and_tilde',      `Sel',   `keyboard grave accent and tilde')dnl
ID(`0036', `kb_comma_and_lt',                `Sel',   `keyboard , and <')dnl
ID(`0037', `kb_period_and_gt',               `Sel',   `keyboard . and >')dnl
ID(`0038', `kb_slash_and_question',          `Sel',   `keyboard / and ?')dnl
ID(`0039', `kb_caps_lock',                   `Sel',   `keyboard Caps Lock')dnl
ID(`003A', `kb_f1',                          `Sel',   `keyboard F1')dnl
ID(`003B', `kb_f2',                          `Sel',   `keyboard F2')dnl
ID(`003C', `kb_f3',                          `Sel',   `keyboard F3')dnl
ID(`003D', `kb_f4',                          `Sel',   `keyboard F4')dnl
ID(`003E', `kb_f5',                          `Sel',   `keyboard F5')dnl
ID(`003F', `kb_f6',                          `Sel',   `keyboard F6')dnl
ID(`0040', `kb_f7',                          `Sel',   `keyboard F7')dnl
ID(`0041', `kb_f8',                          `Sel',   `keyboard F8')dnl
ID(`0042', `kb_f9',                          `Sel',   `keyboard F9')dnl
ID(`0043', `kb_f10',                         `Sel',   `keyboard F10')dnl
ID(`0044', `kb_f11',                         `Sel',   `keyboard F11')dnl
ID(`0045', `kb_f12',                         `Sel',   `keyboard F12')dnl
ID(`0046', `kb_printscreen',                 `Sel',   `keyboard PrintScreen')dnl
ID(`0047', `kb_scroll_lock',                 `Sel',   `keyboard Scroll Lock')dnl
ID(`0048', `kb_pause',                       `Sel',   `keyboard Pause')dnl
ID(`0049', `kb_insert',                      `Sel',   `keyboard Insert')dnl
ID(`004A', `kb_home',                        `Sel',   `keyboard Home')dnl
ID(`004B', `kb_pageup',                      `Sel',   `keyboard PageUp')dnl
ID(`004C', `kb_delete_forward',              `Sel',   `keyboard Delete Forward')dnl
ID(`004D', `kb_end',                         `Sel',   `keyboard End')dnl
ID(`004E', `kb_pagedown',                    `Sel',   `keyboard PageDown')dnl
ID(`004F', `kb_rightarrow',                  `Sel',   `keyboard RightArrow')dnl
ID(`0050', `kb_leftarrow',                   `Sel',   `keyboard LeftArrow')dnl
ID(`0051', `kb_downarrow',                   `Sel',   `keyboard DownArrow')dnl
ID(`0052', `kb_uparrow',                     `Sel',   `keyboard UpArrow')dnl
ID(`0053', `kp_numlock_and_clear',           `Sel',   `keypad Num Lock and Clear')dnl
ID(`0054', `kp_slash',                       `Sel',   `keypad /')dnl
ID(`0055', `kp_star',                        `Sel',   `keypad *')dnl
ID(`0056', `kp_minus',                       `Sel',   `keypad -')dnl
ID(`0057', `kp_plus',                        `Sel',   `keypad +')dnl
ID(`0058', `kp_enter',                       `Sel',   `keypad Enter')dnl
ID(`0059', `kp_1_and_end',                   `Sel',   `keypad 1 and End')dnl
ID(`005A', `kp_2_and_downarrow',             `Sel',   `keypad 2 and Down Arrow')dnl
ID(`005B', `kp_3_and_pagedn',                `Sel',   `keypad 3 and PageDn')dnl
ID(`005C', `kp_4_and_leftarrow',             `Sel',   `keypad 4 and Left Arrow')dnl
ID(`005D', `kp_5',                           `Sel',   `keypad 5')dnl
ID(`005E', `kp_6_and_rightarrow',            `Sel',   `keypad 6 and Right Arrow')dnl
ID(`005F', `kp_7_and_home',                  `Sel',   `keypad 7 and Home')dnl
ID(`0060', `kp_8_and_uparrow',               `Sel',   `keypad 8 and Up Arrow')dnl
ID(`0061', `kp_9_and_pageup',                `Sel',   `keypad 9 and PageUp')dnl
ID(`0062', `kp_0_and_insert',                `Sel',   `keypad 0 and Insert')dnl
ID(`0063', `kp_period_and_delete',           `Sel',   `keypad . and Delete')dnl
ID(`0064', `kb_non_us_backslash_and_pipe',   `Sel',   `keyboard non-US backslash and |')dnl
ID(`0065', `kb_application',                 `Sel',   `keyboard Application')dnl
ID(`0066', `kb_power',                       `Sel',   `keyboard Power')dnl
ID(`0067', `kp_equals',                      `Sel',   `keypad =')dnl
ID(`0068', `kb_f13',                         `Sel',   `keyboard F13')dnl
ID(`0069', `kb_f14',                         `Sel',   `keyboard F14')dnl
ID(`006A', `kb_f15',                         `Sel',   `keyboard F15')dnl
ID(`006B', `kb_f16',                         `Sel',   `keyboard F16')dnl
ID(`006C', `kb_f17',                         `Sel',   `keyboard F17')dnl
ID(`006D', `kb_f18',                         `Sel',   `keyboard F18')dnl
ID(`006E', `kb_f19',                         `Sel',   `keyboard F19')dnl
ID(`006F', `kb_f20',                         `Sel',   `keyboard F20')dnl
ID(`0070', `kb_f21',                         `Sel',   `keyboard F21')dnl
ID(`0071', `kb_f22',                         `Sel',   `keyboard F22')dnl
ID(`0072', `kb_f23',                         `Sel',   `keyboard F23')dnl
ID(`0073', `kb_f24',                         `Sel',   `keyboard F24')dnl
ID(`0074', `kb_execute',                     `Sel',   `keyboard Execute')dnl
ID(`0075', `kb_help',                        `Sel',   `keyboard Help')dnl
ID(`0076', `kb_menu',                        `Sel',   `keyboard Menu')dnl
ID(`0077', `kb_select',                      `Sel',   `keyboard Select')dnl
ID(`0078', `kb_stop',                        `Sel',   `keyboard Stop')dnl
ID(`0079', `kb_again',                       `Sel',   `keyboard Again')dnl
ID(`007A', `kb_undo',                        `Sel',   `keyboard Undo')dnl
ID(`007B', `kb_cut',                         `Sel',   `keyboard Cut')dnl
ID(`007C', `kb_copy',                        `Sel',   `keyboard Copy')dnl
ID(`007D', `kb_paste',                       `Sel',   `keyboard Paste')dnl
ID(`007E', `kb_find',                        `Sel',   `keyboard Find')dnl
ID(`007F', `kb_mute',                        `Sel',   `keyboard Mute')dnl
ID(`0080', `kb_volume_up',                   `Sel',   `keyboard Volume Up')dnl
ID(`0081', `kb_volume_down',                 `Sel',   `keyboard Volume Down')dnl
ID(`0082', `kb_locking_caps_lock',           `Sel',   `keyboard locking Caps Lock')dnl
ID(`0083', `kb_locking_num_lock',            `Sel',   `keyboard locking Num Lock')dnl
ID(`0084', `kb_locking_scroll_lock',         `Sel',   `keyboard locking Scroll Lock')dnl
ID(`0085', `kp_comma',                       `Sel',   `keypad comma')dnl
ID(`0086', `kp_equals_as_400',               `Sel',   `keypad = (AS/400)')dnl
ID(`0087', `kb_intl1',                       `Sel',   `keyboard International1')dnl
ID(`0088', `kb_intl2',                       `Sel',   `keyboard International2')dnl
ID(`0089', `kb_intl3',                       `Sel',   `keyboard International3')dnl
ID(`008A', `kb_intl4',                       `Sel',   `keyboard International4')dnl
ID(`008B', `kb_intl5',                       `Sel',   `keyboard International5')dnl
ID(`008C', `kb_intl6',                       `Sel',   `keyboard International6')dnl
ID(`008D', `kb_intl7',                       `Sel',   `keyboard International7')dnl
ID(`008E', `kb_intl8',                       `Sel',   `keyboard International8')dnl
ID(`008F', `kb_intl9',                       `Sel',   `keyboard International9')dnl
ID(`0090', `kb_lang1',                       `Sel',   `keyboard LANG1')dnl
ID(`0091', `kb_lang2',                       `Sel',   `keyboard LANG2')dnl
ID(`0092', `kb_lang3',                       `Sel',   `keyboard LANG3')dnl
ID(`0093', `kb_lang4',                       `Sel',   `keyboard LANG4')dnl
ID(`0094', `kb_lang5',                       `Sel',   `keyboard LANG5')dnl
ID(`0095', `kb_lang6',                       `Sel',   `keyboard LANG6')dnl
ID(`0096', `kb_lang7',                       `Sel',   `keyboard LANG7')dnl
ID(`0097', `kb_lang8',                       `Sel',   `keyboard LANG8')dnl
ID(`0098', `kb_lang9',                       `Sel',   `keyboard LANG9')dnl
ID(`0099', `kb_alternate_erase',             `Sel',   `keyboard Alternate Erase')dnl
ID(`009A', `kb_sysreq_or_attention',         `Sel',   `keyboard SysReq/Attention')dnl
ID(`009B', `kb_cancel',                      `Sel',   `keyboard Cancel')dnl
ID(`009C', `kb_clear',                       `Sel',   `keyboard Clear')dnl
ID(`009D', `kb_prior',                       `Sel',   `keyboard Prior')dnl
ID(`009E', `kb_return',                      `Sel',   `keyboard Return')dnl
ID(`009F', `kb_separator',                   `Sel',   `keyboard Separator')dnl
ID(`00A0', `kb_out',                         `Sel',   `keyboard Out')dnl
ID(`00A1', `kb_oper',                        `Sel',   `keyboard Oper')dnl
ID(`00A2', `kb_clear_or_again',              `Sel',   `keyboard Clear/Again')dnl
ID(`00A3', `kb_crsel_or_props',              `Sel',   `keyboard CrSel/Props')dnl
ID(`00A4', `kb_exsel',                       `Sel',   `keyboard ExSel')dnl
ID(`00B0', `kp_00',                          `Sel',   `keypad 00')dnl
ID(`00B1', `kp_000',                         `Sel',   `keypad 000')dnl
ID(`00B2', `thousands_separator',            `Sel',   `thousands separator')dnl
ID(`00B3', `decimal_separator',              `Sel',   `decimal separator')dnl
ID(`00B4', `currency_unit',                  `Sel',   `currency unit')dnl
ID(`00B5', `currency_subunit',               `Sel',   `currency sub-unit')dnl
ID(`00B6', `kp_left_paren',                  `Sel',   ``keypad ('')dnl
ID(`00B7', `kp_right_paren',                 `Sel',   ``keypad )'')dnl
ID(`00B8', `kp_left_brace',                  `Sel',   `keypad {')dnl
ID(`00B9', `kp_right_brace',                 `Sel',   `keypad }')dnl
ID(`00BA', `kp_tab',                         `Sel',   `keypad Tab')dnl
ID(`00BB', `kp_backspace',                   `Sel',   `keypad Backspace')dnl
ID(`00BC', `kp_a',                           `Sel',   `keypad A')dnl
ID(`00BD', `kp_b',                           `Sel',   `keypad B')dnl
ID(`00BE', `kp_c',                           `Sel',   `keypad C')dnl
ID(`00BF', `kp_d',                           `Sel',   `keypad D')dnl
ID(`00C0', `kp_e',                           `Sel',   `keypad E')dnl
ID(`00C1', `kp_f',                           `Sel',   `keypad F')dnl
ID(`00C2', `kp_xor',                         `Sel',   `keypad XOR')dnl
ID(`00C3', `kp_caret',                       `Sel',   `keypad ^')dnl
ID(`00C4', `kp_percent',                     `Sel',   `keypad %')dnl
ID(`00C5', `kp_lt',                          `Sel',   `keypad <')dnl
ID(`00C6', `kp_gt',                          `Sel',   `keypad >')dnl
ID(`00C7', `kp_amp',                         `Sel',   `keypad &')dnl
ID(`00C8', `kp_dblamp',                      `Sel',   `keypad &&')dnl
ID(`00C9', `kp_pipe',                        `Sel',   `keypad |')dnl
ID(`00CA', `kp_dblpipe',                     `Sel',   `keypad ||')dnl
ID(`00CB', `kp_colon',                       `Sel',   `keypad :')dnl
ID(`00CC', `kp_number',                      `Sel',   `keypad number')dnl
ID(`00CD', `kp_space',                       `Sel',   `keypad Space')dnl
ID(`00CE', `kp_at',                          `Sel',   `keypad @')dnl
ID(`00CF', `kp_exclamation',                 `Sel',   `keypad !')dnl
ID(`00D0', `kp_mem_store',                   `Sel',   `keypad Memory Store')dnl
ID(`00D1', `kp_mem_recall',                  `Sel',   `keypad Memory Recall')dnl
ID(`00D2', `kp_mem_clear',                   `Sel',   `keypad Memory Clear')dnl
ID(`00D3', `kp_mem_add',                     `Sel',   `keypad Memory Add')dnl
ID(`00D4', `kp_mem_subtract',                `Sel',   `keypad Memory Subtract')dnl
ID(`00D5', `kp_mem_multiply',                `Sel',   `keypad Memory Multiply')dnl
ID(`00D6', `kp_mem_divide',                  `Sel',   `keypad Memory Divide')dnl
ID(`00D7', `kp_plus_minus',                  `Sel',   `keypad +/-')dnl
ID(`00D8', `kp_clear',                       `Sel',   `keypad Clear')dnl
ID(`00D9', `kp_clear_entry',                 `Sel',   `keypad Clear Entry')dnl
ID(`00DA', `kp_binary',                      `Sel',   `keypad Binary')dnl
ID(`00DB', `kp_octal',                       `Sel',   `keypad Octal')dnl
ID(`00DC', `kp_decimal',                     `Sel',   `keypad Decimal')dnl
ID(`00DD', `kp_hexadecimal',                 `Sel',   `keypad Hexadecimal')dnl
ID(`00E0', `kb_leftcontrol',                 `DV',    `keyboard left control')dnl
ID(`00E1', `kb_leftshift',                   `DV',    `keyboard left shift')dnl
ID(`00E2', `kb_leftalt',                     `DV',    `keyboard left alt')dnl
ID(`00E3', `kb_left_gui',                    `DV',    `keyboard left GUI')dnl
ID(`00E4', `kb_rightcontrol',                `DV',    `keyboard right control')dnl
ID(`00E5', `kb_rightshift',                  `DV',    `keyboard right shift')dnl
ID(`00E6', `kb_rightalt',                    `DV',    `keyboard right alt')dnl
ID(`00E7', `kb_right_gui',                   `DV',    `keyboard right GUI')dnl
