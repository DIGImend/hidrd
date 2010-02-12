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
ID(`00', `none',                           `Sel',   `no event')dnl
ID(`01', `kb_error_rollover',              `Sel',   `keyboard ErrorRollOver')dnl
ID(`02', `kb_post_fail',                   `Sel',   `keyboard POSTFail')dnl
ID(`03', `kb_error_undefined',             `Sel',   `keyboard ErrorUndefined')dnl
ID(`04', `kb_a',                           `Sel',   `keyboard a and A')dnl
ID(`05', `kb_b',                           `Sel',   `keyboard b and B')dnl
ID(`06', `kb_c',                           `Sel',   `keyboard c and C')dnl
ID(`07', `kb_d',                           `Sel',   `keyboard d and D')dnl
ID(`08', `kb_e',                           `Sel',   `keyboard e and E')dnl
ID(`09', `kb_f',                           `Sel',   `keyboard f and F')dnl
ID(`0A', `kb_g',                           `Sel',   `keyboard g and G')dnl
ID(`0B', `kb_h',                           `Sel',   `keyboard h and H')dnl
ID(`0C', `kb_i',                           `Sel',   `keyboard i and I')dnl
ID(`0D', `kb_j',                           `Sel',   `keyboard j and J')dnl
ID(`0E', `kb_k',                           `Sel',   `keyboard k and K')dnl
ID(`0F', `kb_l',                           `Sel',   `keyboard l and L')dnl
ID(`10', `kb_m',                           `Sel',   `keyboard m and M')dnl
ID(`11', `kb_n',                           `Sel',   `keyboard n and N')dnl
ID(`12', `kb_o',                           `Sel',   `keyboard o and O')dnl
ID(`13', `kb_p',                           `Sel',   `keyboard p and P')dnl
ID(`14', `kb_q',                           `Sel',   `keyboard q and Q')dnl
ID(`15', `kb_r',                           `Sel',   `keyboard r and R')dnl
ID(`16', `kb_s',                           `Sel',   `keyboard s and S')dnl
ID(`17', `kb_t',                           `Sel',   `keyboard t and T')dnl
ID(`18', `kb_u',                           `Sel',   `keyboard u and U')dnl
ID(`19', `kb_v',                           `Sel',   `keyboard v and V')dnl
ID(`1A', `kb_w',                           `Sel',   `keyboard w and W')dnl
ID(`1B', `kb_x',                           `Sel',   `keyboard x and X')dnl
ID(`1C', `kb_y',                           `Sel',   `keyboard y and Y')dnl
ID(`1D', `kb_z',                           `Sel',   `keyboard z and Z')dnl
ID(`1E', `kb_1_and_exclam',                `Sel',   `keyboard 1 and !')dnl
ID(`1F', `kb_2_and_at',                    `Sel',   `keyboard 2 and @')dnl
ID(`20', `kb_3_and_number',                `Sel',   `keyboard 3 and number')dnl
ID(`21', `kb_4_and_dollar',                `Sel',   `keyboard 4 and $')dnl
ID(`22', `kb_5_and_percent',               `Sel',   `keyboard 5 and %')dnl
ID(`23', `kb_6_and_caret',                 `Sel',   `keyboard 6 and ^')dnl
ID(`24', `kb_7_and_amp',                   `Sel',   `keyboard 7 and &')dnl
ID(`25', `kb_8_and_star',                  `Sel',   `keyboard 8 and *')dnl
ID(`26', `kb_9_and_left_paren',            `Sel',   ``keyboard 9 and ('')dnl
ID(`27', `kb_0_and_right_paren',           `Sel',   ``keyboard 0 and )'')dnl
ID(`28', `kb_enter',                       `Sel',   `keyboard Return (ENTER)')dnl
ID(`29', `kb_escape',                      `Sel',   `keyboard Escape')dnl
ID(`2A', `kb_delete',                      `Sel',   `keyboard Delete (Backspace)')dnl
ID(`2B', `kb_tab',                         `Sel',   `keyboard Tab')dnl
ID(`2C', `kb_spacebar',                    `Sel',   `keyboard spacebar')dnl
ID(`2D', `kb_minus_and_underscore',        `Sel',   `keyboard - and _ (underscore)')dnl
ID(`2E', `kb_equals_and_plus',             `Sel',   `keyboard = and +')dnl
ID(`2F', `kb_lboxbracket_and_lbrace',      `Sel',   `keyboard [ and {')dnl
ID(`30', `kb_rboxbracket_and_rbrace',      `Sel',   `keyboard ] and }')dnl
ID(`31', `kb_backslash_and_pipe',          `Sel',   `keyboard backslash and |')dnl
ID(`32', `kb_non_us_number_and_tilde',     `Sel',   `keyboard non-US number and ~')dnl
ID(`33', `kb_semicolon_and_colon',         `Sel',   `keyboard ; and :')dnl
ID(`34', `kb_quot_and_dblquot',            `Sel',   `keyboard ‘ and “')dnl
ID(`35', `kb_grave_accent_and_tilde',      `Sel',   `keyboard grave accent and tilde')dnl
ID(`36', `kb_comma_and_lt',                `Sel',   `keyboard , and <')dnl
ID(`37', `kb_period_and_gt',               `Sel',   `keyboard . and >')dnl
ID(`38', `kb_slash_and_question',          `Sel',   `keyboard / and ?')dnl
ID(`39', `kb_caps_lock',                   `Sel',   `keyboard Caps Lock')dnl
ID(`3A', `kb_f1',                          `Sel',   `keyboard F1')dnl
ID(`3B', `kb_f2',                          `Sel',   `keyboard F2')dnl
ID(`3C', `kb_f3',                          `Sel',   `keyboard F3')dnl
ID(`3D', `kb_f4',                          `Sel',   `keyboard F4')dnl
ID(`3E', `kb_f5',                          `Sel',   `keyboard F5')dnl
ID(`3F', `kb_f6',                          `Sel',   `keyboard F6')dnl
ID(`40', `kb_f7',                          `Sel',   `keyboard F7')dnl
ID(`41', `kb_f8',                          `Sel',   `keyboard F8')dnl
ID(`42', `kb_f9',                          `Sel',   `keyboard F9')dnl
ID(`43', `kb_f10',                         `Sel',   `keyboard F10')dnl
ID(`44', `kb_f11',                         `Sel',   `keyboard F11')dnl
ID(`45', `kb_f12',                         `Sel',   `keyboard F12')dnl
ID(`46', `kb_printscreen',                 `Sel',   `keyboard PrintScreen')dnl
ID(`47', `kb_scroll_lock',                 `Sel',   `keyboard Scroll Lock')dnl
ID(`48', `kb_pause',                       `Sel',   `keyboard Pause')dnl
ID(`49', `kb_insert',                      `Sel',   `keyboard Insert')dnl
ID(`4A', `kb_home',                        `Sel',   `keyboard Home')dnl
ID(`4B', `kb_pageup',                      `Sel',   `keyboard PageUp')dnl
ID(`4C', `kb_delete_forward',              `Sel',   `keyboard Delete Forward')dnl
ID(`4D', `kb_end',                         `Sel',   `keyboard End')dnl
ID(`4E', `kb_pagedown',                    `Sel',   `keyboard PageDown')dnl
ID(`4F', `kb_rightarrow',                  `Sel',   `keyboard RightArrow')dnl
ID(`50', `kb_leftarrow',                   `Sel',   `keyboard LeftArrow')dnl
ID(`51', `kb_downarrow',                   `Sel',   `keyboard DownArrow')dnl
ID(`52', `kb_uparrow',                     `Sel',   `keyboard UpArrow')dnl
ID(`53', `kp_numlock_and_clear',           `Sel',   `keypad Num Lock and Clear')dnl
ID(`54', `kp_slash',                       `Sel',   `keypad /')dnl
ID(`55', `kp_star',                        `Sel',   `keypad *')dnl
ID(`56', `kp_minus',                       `Sel',   `keypad -')dnl
ID(`57', `kp_plus',                        `Sel',   `keypad +')dnl
ID(`58', `kp_enter',                       `Sel',   `keypad Enter')dnl
ID(`59', `kp_1_and_end',                   `Sel',   `keypad 1 and End')dnl
ID(`5A', `kp_2_and_downarrow',             `Sel',   `keypad 2 and Down Arrow')dnl
ID(`5B', `kp_3_and_pagedn',                `Sel',   `keypad 3 and PageDn')dnl
ID(`5C', `kp_4_and_leftarrow',             `Sel',   `keypad 4 and Left Arrow')dnl
ID(`5D', `kp_5',                           `Sel',   `keypad 5')dnl
ID(`5E', `kp_6_and_rightarrow',            `Sel',   `keypad 6 and Right Arrow')dnl
ID(`5F', `kp_7_and_home',                  `Sel',   `keypad 7 and Home')dnl
ID(`60', `kp_8_and_uparrow',               `Sel',   `keypad 8 and Up Arrow')dnl
ID(`61', `kp_9_and_pageup',                `Sel',   `keypad 9 and PageUp')dnl
ID(`62', `kp_0_and_insert',                `Sel',   `keypad 0 and Insert')dnl
ID(`63', `kp_period_and_delete',           `Sel',   `keypad . and Delete')dnl
ID(`64', `kb_non_us_backslash_and_pipe',   `Sel',   `keyboard non-US backslash and |')dnl
ID(`65', `kb_application',                 `Sel',   `keyboard Application')dnl
ID(`66', `kb_power',                       `Sel',   `keyboard Power')dnl
ID(`67', `kp_equals',                      `Sel',   `keypad =')dnl
ID(`68', `kb_f13',                         `Sel',   `keyboard F13')dnl
ID(`69', `kb_f14',                         `Sel',   `keyboard F14')dnl
ID(`6A', `kb_f15',                         `Sel',   `keyboard F15')dnl
ID(`6B', `kb_f16',                         `Sel',   `keyboard F16')dnl
ID(`6C', `kb_f17',                         `Sel',   `keyboard F17')dnl
ID(`6D', `kb_f18',                         `Sel',   `keyboard F18')dnl
ID(`6E', `kb_f19',                         `Sel',   `keyboard F19')dnl
ID(`6F', `kb_f20',                         `Sel',   `keyboard F20')dnl
ID(`70', `kb_f21',                         `Sel',   `keyboard F21')dnl
ID(`71', `kb_f22',                         `Sel',   `keyboard F22')dnl
ID(`72', `kb_f23',                         `Sel',   `keyboard F23')dnl
ID(`73', `kb_f24',                         `Sel',   `keyboard F24')dnl
ID(`74', `kb_execute',                     `Sel',   `keyboard Execute')dnl
ID(`75', `kb_help',                        `Sel',   `keyboard Help')dnl
ID(`76', `kb_menu',                        `Sel',   `keyboard Menu')dnl
ID(`77', `kb_select',                      `Sel',   `keyboard Select')dnl
ID(`78', `kb_stop',                        `Sel',   `keyboard Stop')dnl
ID(`79', `kb_again',                       `Sel',   `keyboard Again')dnl
ID(`7A', `kb_undo',                        `Sel',   `keyboard Undo')dnl
ID(`7B', `kb_cut',                         `Sel',   `keyboard Cut')dnl
ID(`7C', `kb_copy',                        `Sel',   `keyboard Copy')dnl
ID(`7D', `kb_paste',                       `Sel',   `keyboard Paste')dnl
ID(`7E', `kb_find',                        `Sel',   `keyboard Find')dnl
ID(`7F', `kb_mute',                        `Sel',   `keyboard Mute')dnl
ID(`80', `kb_volume_up',                   `Sel',   `keyboard Volume Up')dnl
ID(`81', `kb_volume_down',                 `Sel',   `keyboard Volume Down')dnl
ID(`82', `kb_locking_caps_lock',           `Sel',   `keyboard locking Caps Lock')dnl
ID(`83', `kb_locking_num_lock',            `Sel',   `keyboard locking Num Lock')dnl
ID(`84', `kb_locking_scroll_lock',         `Sel',   `keyboard locking Scroll Lock')dnl
ID(`85', `kp_comma',                       `Sel',   `keypad comma')dnl
ID(`86', `kp_equals_as_400',               `Sel',   `keypad = (AS/400)')dnl
ID(`87', `kb_intl1',                       `Sel',   `keyboard International1')dnl
ID(`88', `kb_intl2',                       `Sel',   `keyboard International2')dnl
ID(`89', `kb_intl3',                       `Sel',   `keyboard International3')dnl
ID(`8A', `kb_intl4',                       `Sel',   `keyboard International4')dnl
ID(`8B', `kb_intl5',                       `Sel',   `keyboard International5')dnl
ID(`8C', `kb_intl6',                       `Sel',   `keyboard International6')dnl
ID(`8D', `kb_intl7',                       `Sel',   `keyboard International7')dnl
ID(`8E', `kb_intl8',                       `Sel',   `keyboard International8')dnl
ID(`8F', `kb_intl9',                       `Sel',   `keyboard International9')dnl
ID(`90', `kb_lang1',                       `Sel',   `keyboard LANG1')dnl
ID(`91', `kb_lang2',                       `Sel',   `keyboard LANG2')dnl
ID(`92', `kb_lang3',                       `Sel',   `keyboard LANG3')dnl
ID(`93', `kb_lang4',                       `Sel',   `keyboard LANG4')dnl
ID(`94', `kb_lang5',                       `Sel',   `keyboard LANG5')dnl
ID(`95', `kb_lang6',                       `Sel',   `keyboard LANG6')dnl
ID(`96', `kb_lang7',                       `Sel',   `keyboard LANG7')dnl
ID(`97', `kb_lang8',                       `Sel',   `keyboard LANG8')dnl
ID(`98', `kb_lang9',                       `Sel',   `keyboard LANG9')dnl
ID(`99', `kb_alternate_erase',             `Sel',   `keyboard Alternate Erase')dnl
ID(`9A', `kb_sysreq_or_attention',         `Sel',   `keyboard SysReq/Attention')dnl
ID(`9B', `kb_cancel',                      `Sel',   `keyboard Cancel')dnl
ID(`9C', `kb_clear',                       `Sel',   `keyboard Clear')dnl
ID(`9D', `kb_prior',                       `Sel',   `keyboard Prior')dnl
ID(`9E', `kb_return',                      `Sel',   `keyboard Return')dnl
ID(`9F', `kb_separator',                   `Sel',   `keyboard Separator')dnl
ID(`A0', `kb_out',                         `Sel',   `keyboard Out')dnl
ID(`A1', `kb_oper',                        `Sel',   `keyboard Oper')dnl
ID(`A2', `kb_clear_or_again',              `Sel',   `keyboard Clear/Again')dnl
ID(`A3', `kb_crsel_or_props',              `Sel',   `keyboard CrSel/Props')dnl
ID(`A4', `kb_exsel',                       `Sel',   `keyboard ExSel')dnl
ID(`B0', `kp_00',                          `Sel',   `keypad 00')dnl
ID(`B1', `kp_000',                         `Sel',   `keypad 000')dnl
ID(`B2', `thousands_separator',            `Sel',   `thousands separator')dnl
ID(`B3', `decimal_separator',              `Sel',   `decimal separator')dnl
ID(`B4', `currency_unit',                  `Sel',   `currency unit')dnl
ID(`B5', `currency_subunit',               `Sel',   `currency sub-unit')dnl
ID(`B6', `kp_left_paren',                  `Sel',   ``keypad ('')dnl
ID(`B7', `kp_right_paren',                 `Sel',   ``keypad )'')dnl
ID(`B8', `kp_left_brace',                  `Sel',   `keypad {')dnl
ID(`B9', `kp_right_brace',                 `Sel',   `keypad }')dnl
ID(`BA', `kp_tab',                         `Sel',   `keypad Tab')dnl
ID(`BB', `kp_backspace',                   `Sel',   `keypad Backspace')dnl
ID(`BC', `kp_a',                           `Sel',   `keypad A')dnl
ID(`BD', `kp_b',                           `Sel',   `keypad B')dnl
ID(`BE', `kp_c',                           `Sel',   `keypad C')dnl
ID(`BF', `kp_d',                           `Sel',   `keypad D')dnl
ID(`C0', `kp_e',                           `Sel',   `keypad E')dnl
ID(`C1', `kp_f',                           `Sel',   `keypad F')dnl
ID(`C2', `kp_xor',                         `Sel',   `keypad XOR')dnl
ID(`C3', `kp_caret',                       `Sel',   `keypad ^')dnl
ID(`C4', `kp_percent',                     `Sel',   `keypad %')dnl
ID(`C5', `kp_lt',                          `Sel',   `keypad <')dnl
ID(`C6', `kp_gt',                          `Sel',   `keypad >')dnl
ID(`C7', `kp_amp',                         `Sel',   `keypad &')dnl
ID(`C8', `kp_dblamp',                      `Sel',   `keypad &&')dnl
ID(`C9', `kp_pipe',                        `Sel',   `keypad |')dnl
ID(`CA', `kp_dblpipe',                     `Sel',   `keypad ||')dnl
ID(`CB', `kp_colon',                       `Sel',   `keypad :')dnl
ID(`CC', `kp_number',                      `Sel',   `keypad number')dnl
ID(`CD', `kp_space',                       `Sel',   `keypad Space')dnl
ID(`CE', `kp_at',                          `Sel',   `keypad @')dnl
ID(`CF', `kp_exclamation',                 `Sel',   `keypad !')dnl
ID(`D0', `kp_mem_store',                   `Sel',   `keypad Memory Store')dnl
ID(`D1', `kp_mem_recall',                  `Sel',   `keypad Memory Recall')dnl
ID(`D2', `kp_mem_clear',                   `Sel',   `keypad Memory Clear')dnl
ID(`D3', `kp_mem_add',                     `Sel',   `keypad Memory Add')dnl
ID(`D4', `kp_mem_subtract',                `Sel',   `keypad Memory Subtract')dnl
ID(`D5', `kp_mem_multiply',                `Sel',   `keypad Memory Multiply')dnl
ID(`D6', `kp_mem_divide',                  `Sel',   `keypad Memory Divide')dnl
ID(`D7', `kp_plus_minus',                  `Sel',   `keypad +/-')dnl
ID(`D8', `kp_clear',                       `Sel',   `keypad Clear')dnl
ID(`D9', `kp_clear_entry',                 `Sel',   `keypad Clear Entry')dnl
ID(`DA', `kp_binary',                      `Sel',   `keypad Binary')dnl
ID(`DB', `kp_octal',                       `Sel',   `keypad Octal')dnl
ID(`DC', `kp_decimal',                     `Sel',   `keypad Decimal')dnl
ID(`DD', `kp_hexadecimal',                 `Sel',   `keypad Hexadecimal')dnl
ID(`E0', `kb_leftcontrol',                 `DV',    `keyboard left control')dnl
ID(`E1', `kb_leftshift',                   `DV',    `keyboard left shift')dnl
ID(`E2', `kb_leftalt',                     `DV',    `keyboard left alt')dnl
ID(`E3', `kb_left_gui',                    `DV',    `keyboard left GUI')dnl
ID(`E4', `kb_rightcontrol',                `DV',    `keyboard right control')dnl
ID(`E5', `kb_rightshift',                  `DV',    `keyboard right shift')dnl
ID(`E6', `kb_rightalt',                    `DV',    `keyboard right alt')dnl
ID(`E7', `kb_right_gui',                   `DV',    `keyboard right GUI')dnl
