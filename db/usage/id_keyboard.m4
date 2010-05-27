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
dnl     * ID token (non-capitalized, underscores for spaces)
dnl     * Usage types (comma separated, case as per specification)
dnl     * ID description (non-capitalized)
dnl
ID(`0000', `none',                           `Sel',   `no event')dnl
ID(`0001', `KB_ErrorRollOver',               `Sel',   `keyboard ErrorRollOver')dnl
ID(`0002', `KB_POSTFail',                    `Sel',   `keyboard POSTFail')dnl
ID(`0003', `KB_ErrorUndefined',              `Sel',   `keyboard ErrorUndefined')dnl
ID(`0004', `KB_A',                           `Sel',   `keyboard a and A')dnl
ID(`0005', `KB_B',                           `Sel',   `keyboard b and B')dnl
ID(`0006', `KB_C',                           `Sel',   `keyboard c and C')dnl
ID(`0007', `KB_D',                           `Sel',   `keyboard d and D')dnl
ID(`0008', `KB_E',                           `Sel',   `keyboard e and E')dnl
ID(`0009', `KB_F',                           `Sel',   `keyboard f and F')dnl
ID(`000A', `KB_G',                           `Sel',   `keyboard g and G')dnl
ID(`000B', `KB_H',                           `Sel',   `keyboard h and H')dnl
ID(`000C', `KB_I',                           `Sel',   `keyboard i and I')dnl
ID(`000D', `KB_J',                           `Sel',   `keyboard j and J')dnl
ID(`000E', `KB_K',                           `Sel',   `keyboard k and K')dnl
ID(`000F', `KB_L',                           `Sel',   `keyboard l and L')dnl
ID(`0010', `KB_M',                           `Sel',   `keyboard m and M')dnl
ID(`0011', `KB_N',                           `Sel',   `keyboard n and N')dnl
ID(`0012', `KB_O',                           `Sel',   `keyboard o and O')dnl
ID(`0013', `KB_P',                           `Sel',   `keyboard p and P')dnl
ID(`0014', `KB_Q',                           `Sel',   `keyboard q and Q')dnl
ID(`0015', `KB_R',                           `Sel',   `keyboard r and R')dnl
ID(`0016', `KB_S',                           `Sel',   `keyboard s and S')dnl
ID(`0017', `KB_T',                           `Sel',   `keyboard t and T')dnl
ID(`0018', `KB_U',                           `Sel',   `keyboard u and U')dnl
ID(`0019', `KB_V',                           `Sel',   `keyboard v and V')dnl
ID(`001A', `KB_W',                           `Sel',   `keyboard w and W')dnl
ID(`001B', `KB_X',                           `Sel',   `keyboard x and X')dnl
ID(`001C', `KB_Y',                           `Sel',   `keyboard y and Y')dnl
ID(`001D', `KB_Z',                           `Sel',   `keyboard z and Z')dnl
ID(`001E', `KB_1_and_exclam',                `Sel',   `keyboard 1 and !')dnl
ID(`001F', `KB_2_and_at',                    `Sel',   `keyboard 2 and @')dnl
ID(`0020', `KB_3_and_number',                `Sel',   `keyboard 3 and number')dnl
ID(`0021', `KB_4_and_dollar',                `Sel',   `keyboard 4 and $')dnl
ID(`0022', `KB_5_and_percent',               `Sel',   `keyboard 5 and %')dnl
ID(`0023', `KB_6_and_caret',                 `Sel',   `keyboard 6 and ^')dnl
ID(`0024', `KB_7_and_amp',                   `Sel',   `keyboard 7 and &')dnl
ID(`0025', `KB_8_and_star',                  `Sel',   `keyboard 8 and *')dnl
ID(`0026', `KB_9_and_left_paren',            `Sel',   `keyboard 9 and left parenthesis')dnl
ID(`0027', `KB_0_and_right_paren',           `Sel',   `keyboard 0 and right parenthesis')dnl
ID(`0028', `KB_Enter',                       `Sel',   `keyboard Return (ENTER)')dnl
ID(`0029', `KB_Escape',                      `Sel',   `keyboard Escape')dnl
ID(`002A', `KB_Delete',                      `Sel',   `keyboard Delete (Backspace)')dnl
ID(`002B', `KB_Tab',                         `Sel',   `keyboard Tab')dnl
ID(`002C', `KB_spacebar',                    `Sel',   `keyboard spacebar')dnl
ID(`002D', `KB_minus_and_underscore',        `Sel',   `keyboard - and _ (underscore)')dnl
ID(`002E', `KB_equals_and_plus',             `Sel',   `keyboard = and +')dnl
ID(`002F', `KB_lboxbracket_and_lbrace',      `Sel',   `keyboard [ and {')dnl
ID(`0030', `KB_rboxbracket_and_rbrace',      `Sel',   `keyboard ] and }')dnl
ID(`0031', `KB_backslash_and_pipe',          `Sel',   `keyboard backslash and |')dnl
ID(`0032', `KB_non_US_number_and_tilde',     `Sel',   `keyboard non-US number and ~')dnl
ID(`0033', `KB_semicolon_and_colon',         `Sel',   `keyboard ; and :')dnl
ID(`0034', `KB_quot_and_dblquot',            `Sel',   `keyboard ‘ and “')dnl
ID(`0035', `KB_grave_accent_and_tilde',      `Sel',   `keyboard grave accent and tilde')dnl
ID(`0036', `KB_comma_and_lt',                `Sel',   `keyboard , and <')dnl
ID(`0037', `KB_period_and_gt',               `Sel',   `keyboard . and >')dnl
ID(`0038', `KB_slash_and_question',          `Sel',   `keyboard / and ?')dnl
ID(`0039', `KB_Caps_Lock',                   `Sel',   `keyboard Caps Lock')dnl
ID(`003A', `KB_F1',                          `Sel',   `keyboard F1')dnl
ID(`003B', `KB_F2',                          `Sel',   `keyboard F2')dnl
ID(`003C', `KB_F3',                          `Sel',   `keyboard F3')dnl
ID(`003D', `KB_F4',                          `Sel',   `keyboard F4')dnl
ID(`003E', `KB_F5',                          `Sel',   `keyboard F5')dnl
ID(`003F', `KB_F6',                          `Sel',   `keyboard F6')dnl
ID(`0040', `KB_F7',                          `Sel',   `keyboard F7')dnl
ID(`0041', `KB_F8',                          `Sel',   `keyboard F8')dnl
ID(`0042', `KB_F9',                          `Sel',   `keyboard F9')dnl
ID(`0043', `KB_F10',                         `Sel',   `keyboard F10')dnl
ID(`0044', `KB_F11',                         `Sel',   `keyboard F11')dnl
ID(`0045', `KB_F12',                         `Sel',   `keyboard F12')dnl
ID(`0046', `KB_Print_Screen',                `Sel',   `keyboard Print Screen')dnl
ID(`0047', `KB_Scroll_Lock',                 `Sel',   `keyboard Scroll Lock')dnl
ID(`0048', `KB_Pause',                       `Sel',   `keyboard Pause')dnl
ID(`0049', `KB_Insert',                      `Sel',   `keyboard Insert')dnl
ID(`004A', `KB_Home',                        `Sel',   `keyboard Home')dnl
ID(`004B', `KB_PageUp',                      `Sel',   `keyboard PageUp')dnl
ID(`004C', `KB_Delete_Forward',              `Sel',   `keyboard Delete Forward')dnl
ID(`004D', `KB_End',                         `Sel',   `keyboard End')dnl
ID(`004E', `KB_PageDown',                    `Sel',   `keyboard PageDown')dnl
ID(`004F', `KB_RightArrow',                  `Sel',   `keyboard RightArrow')dnl
ID(`0050', `KB_LeftArrow',                   `Sel',   `keyboard LeftArrow')dnl
ID(`0051', `KB_DownArrow',                   `Sel',   `keyboard DownArrow')dnl
ID(`0052', `KB_UpArrow',                     `Sel',   `keyboard UpArrow')dnl
ID(`0053', `KP_Num_Lock_and_Clear',          `Sel',   `keypad Num Lock and Clear')dnl
ID(`0054', `KP_slash',                       `Sel',   `keypad /')dnl
ID(`0055', `KP_star',                        `Sel',   `keypad *')dnl
ID(`0056', `KP_minus',                       `Sel',   `keypad -')dnl
ID(`0057', `KP_plus',                        `Sel',   `keypad +')dnl
ID(`0058', `KP_enter',                       `Sel',   `keypad Enter')dnl
ID(`0059', `KP_1_and_End',                   `Sel',   `keypad 1 and End')dnl
ID(`005A', `KP_2_and_DownArrow',             `Sel',   `keypad 2 and Down Arrow')dnl
ID(`005B', `KP_3_and_PageDn',                `Sel',   `keypad 3 and PageDn')dnl
ID(`005C', `KP_4_and_LeftArrow',             `Sel',   `keypad 4 and Left Arrow')dnl
ID(`005D', `KP_5',                           `Sel',   `keypad 5')dnl
ID(`005E', `KP_6_and_RightArrow',            `Sel',   `keypad 6 and Right Arrow')dnl
ID(`005F', `KP_7_and_Home',                  `Sel',   `keypad 7 and Home')dnl
ID(`0060', `KP_8_and_UpArrow',               `Sel',   `keypad 8 and Up Arrow')dnl
ID(`0061', `KP_9_and_PageUp',                `Sel',   `keypad 9 and PageUp')dnl
ID(`0062', `KP_0_and_Insert',                `Sel',   `keypad 0 and Insert')dnl
ID(`0063', `KP_period_and_Delete',           `Sel',   `keypad . and Delete')dnl
ID(`0064', `KB_non_US_backslash_and_pipe',   `Sel',   `keyboard non-US backslash and |')dnl
ID(`0065', `KB_Application',                 `Sel',   `keyboard Application')dnl
ID(`0066', `KB_Power',                       `Sel',   `keyboard Power')dnl
ID(`0067', `KP_equals',                      `Sel',   `keypad =')dnl
ID(`0068', `KB_F13',                         `Sel',   `keyboard F13')dnl
ID(`0069', `KB_F14',                         `Sel',   `keyboard F14')dnl
ID(`006A', `KB_F15',                         `Sel',   `keyboard F15')dnl
ID(`006B', `KB_F16',                         `Sel',   `keyboard F16')dnl
ID(`006C', `KB_F17',                         `Sel',   `keyboard F17')dnl
ID(`006D', `KB_F18',                         `Sel',   `keyboard F18')dnl
ID(`006E', `KB_F19',                         `Sel',   `keyboard F19')dnl
ID(`006F', `KB_F20',                         `Sel',   `keyboard F20')dnl
ID(`0070', `KB_F21',                         `Sel',   `keyboard F21')dnl
ID(`0071', `KB_F22',                         `Sel',   `keyboard F22')dnl
ID(`0072', `KB_F23',                         `Sel',   `keyboard F23')dnl
ID(`0073', `KB_F24',                         `Sel',   `keyboard F24')dnl
ID(`0074', `KB_Execute',                     `Sel',   `keyboard Execute')dnl
ID(`0075', `KB_Help',                        `Sel',   `keyboard Help')dnl
ID(`0076', `KB_Menu',                        `Sel',   `keyboard Menu')dnl
ID(`0077', `KB_Select',                      `Sel',   `keyboard Select')dnl
ID(`0078', `KB_Stop',                        `Sel',   `keyboard Stop')dnl
ID(`0079', `KB_Again',                       `Sel',   `keyboard Again')dnl
ID(`007A', `KB_Undo',                        `Sel',   `keyboard Undo')dnl
ID(`007B', `KB_Cut',                         `Sel',   `keyboard Cut')dnl
ID(`007C', `KB_Copy',                        `Sel',   `keyboard Copy')dnl
ID(`007D', `KB_Paste',                       `Sel',   `keyboard Paste')dnl
ID(`007E', `KB_Find',                        `Sel',   `keyboard Find')dnl
ID(`007F', `KB_Mute',                        `Sel',   `keyboard Mute')dnl
ID(`0080', `KB_Volume_Up',                   `Sel',   `keyboard Volume Up')dnl
ID(`0081', `KB_Volume_Down',                 `Sel',   `keyboard Volume Down')dnl
ID(`0082', `KB_locking_Caps_Lock',           `Sel',   `keyboard locking Caps Lock')dnl
ID(`0083', `KB_locking_Num_Lock',            `Sel',   `keyboard locking Num Lock')dnl
ID(`0084', `KB_locking_Scroll_Lock',         `Sel',   `keyboard locking Scroll Lock')dnl
ID(`0085', `KP_comma',                       `Sel',   `keypad comma')dnl
ID(`0086', `KP_equals_AS_400',               `Sel',   `keypad = (AS/400)')dnl
ID(`0087', `KB_Intl1',                       `Sel',   `keyboard International1')dnl
ID(`0088', `KB_Intl2',                       `Sel',   `keyboard International2')dnl
ID(`0089', `KB_Intl3',                       `Sel',   `keyboard International3')dnl
ID(`008A', `KB_Intl4',                       `Sel',   `keyboard International4')dnl
ID(`008B', `KB_Intl5',                       `Sel',   `keyboard International5')dnl
ID(`008C', `KB_Intl6',                       `Sel',   `keyboard International6')dnl
ID(`008D', `KB_Intl7',                       `Sel',   `keyboard International7')dnl
ID(`008E', `KB_Intl8',                       `Sel',   `keyboard International8')dnl
ID(`008F', `KB_Intl9',                       `Sel',   `keyboard International9')dnl
ID(`0090', `KB_LANG1',                       `Sel',   `keyboard LANG1')dnl
ID(`0091', `KB_LANG2',                       `Sel',   `keyboard LANG2')dnl
ID(`0092', `KB_LANG3',                       `Sel',   `keyboard LANG3')dnl
ID(`0093', `KB_LANG4',                       `Sel',   `keyboard LANG4')dnl
ID(`0094', `KB_LANG5',                       `Sel',   `keyboard LANG5')dnl
ID(`0095', `KB_LANG6',                       `Sel',   `keyboard LANG6')dnl
ID(`0096', `KB_LANG7',                       `Sel',   `keyboard LANG7')dnl
ID(`0097', `KB_LANG8',                       `Sel',   `keyboard LANG8')dnl
ID(`0098', `KB_LANG9',                       `Sel',   `keyboard LANG9')dnl
ID(`0099', `KB_Alternate_Erase',             `Sel',   `keyboard Alternate Erase')dnl
ID(`009A', `KB_SysReq_or_Attention',         `Sel',   `keyboard SysReq/Attention')dnl
ID(`009B', `KB_Cancel',                      `Sel',   `keyboard Cancel')dnl
ID(`009C', `KB_Clear',                       `Sel',   `keyboard Clear')dnl
ID(`009D', `KB_Prior',                       `Sel',   `keyboard Prior')dnl
ID(`009E', `KB_Return',                      `Sel',   `keyboard Return')dnl
ID(`009F', `KB_Separator',                   `Sel',   `keyboard Separator')dnl
ID(`00A0', `KB_Out',                         `Sel',   `keyboard Out')dnl
ID(`00A1', `KB_Oper',                        `Sel',   `keyboard Oper')dnl
ID(`00A2', `KB_Clear_or_Again',              `Sel',   `keyboard Clear/Again')dnl
ID(`00A3', `KB_Crsel_or_Props',              `Sel',   `keyboard CrSel/Props')dnl
ID(`00A4', `KB_ExSel',                       `Sel',   `keyboard ExSel')dnl
ID(`00B0', `KP_00',                          `Sel',   `keypad 00')dnl
ID(`00B1', `KP_000',                         `Sel',   `keypad 000')dnl
ID(`00B2', `thousands_separator',            `Sel',   `thousands separator')dnl
ID(`00B3', `decimal_separator',              `Sel',   `decimal separator')dnl
ID(`00B4', `currency_unit',                  `Sel',   `currency unit')dnl
ID(`00B5', `currency_subunit',               `Sel',   `currency sub-unit')dnl
ID(`00B6', `KP_left_paren',                  `Sel',   `keypad left parenthesis')dnl
ID(`00B7', `KP_right_paren',                 `Sel',   `keypad right parenthesis')dnl
ID(`00B8', `KP_left_brace',                  `Sel',   `keypad {')dnl
ID(`00B9', `KP_right_brace',                 `Sel',   `keypad }')dnl
ID(`00BA', `KP_Tab',                         `Sel',   `keypad Tab')dnl
ID(`00BB', `KP_Backspace',                   `Sel',   `keypad Backspace')dnl
ID(`00BC', `KP_A',                           `Sel',   `keypad A')dnl
ID(`00BD', `KP_B',                           `Sel',   `keypad B')dnl
ID(`00BE', `KP_C',                           `Sel',   `keypad C')dnl
ID(`00BF', `KP_D',                           `Sel',   `keypad D')dnl
ID(`00C0', `KP_E',                           `Sel',   `keypad E')dnl
ID(`00C1', `KP_F',                           `Sel',   `keypad F')dnl
ID(`00C2', `KP_XOR',                         `Sel',   `keypad XOR')dnl
ID(`00C3', `KP_caret',                       `Sel',   `keypad ^')dnl
ID(`00C4', `KP_percent',                     `Sel',   `keypad %')dnl
ID(`00C5', `KP_lt',                          `Sel',   `keypad <')dnl
ID(`00C6', `KP_gt',                          `Sel',   `keypad >')dnl
ID(`00C7', `KP_amp',                         `Sel',   `keypad &')dnl
ID(`00C8', `KP_dblamp',                      `Sel',   `keypad &&')dnl
ID(`00C9', `KP_pipe',                        `Sel',   `keypad |')dnl
ID(`00CA', `KP_dblpipe',                     `Sel',   `keypad ||')dnl
ID(`00CB', `KP_colon',                       `Sel',   `keypad :')dnl
ID(`00CC', `KP_number',                      `Sel',   `keypad number')dnl
ID(`00CD', `KP_Space',                       `Sel',   `keypad Space')dnl
ID(`00CE', `KP_at',                          `Sel',   `keypad @')dnl
ID(`00CF', `KP_exclamation',                 `Sel',   `keypad !')dnl
ID(`00D0', `KP_Mem_Store',                   `Sel',   `keypad Memory Store')dnl
ID(`00D1', `KP_Mem_Recall',                  `Sel',   `keypad Memory Recall')dnl
ID(`00D2', `KP_Mem_Clear',                   `Sel',   `keypad Memory Clear')dnl
ID(`00D3', `KP_Mem_Add',                     `Sel',   `keypad Memory Add')dnl
ID(`00D4', `KP_Mem_Subtract',                `Sel',   `keypad Memory Subtract')dnl
ID(`00D5', `KP_Mem_Multiply',                `Sel',   `keypad Memory Multiply')dnl
ID(`00D6', `KP_Mem_Divide',                  `Sel',   `keypad Memory Divide')dnl
ID(`00D7', `KP_plus_minus',                  `Sel',   `keypad +/-')dnl
ID(`00D8', `KP_Clear',                       `Sel',   `keypad Clear')dnl
ID(`00D9', `KP_Clear_Entry',                 `Sel',   `keypad Clear Entry')dnl
ID(`00DA', `KP_Binary',                      `Sel',   `keypad Binary')dnl
ID(`00DB', `KP_Octal',                       `Sel',   `keypad Octal')dnl
ID(`00DC', `KP_Decimal',                     `Sel',   `keypad Decimal')dnl
ID(`00DD', `KP_Hexadecimal',                 `Sel',   `keypad Hexadecimal')dnl
ID(`00E0', `KB_leftcontrol',                 `DV',    `keyboard left control')dnl
ID(`00E1', `KB_leftshift',                   `DV',    `keyboard left shift')dnl
ID(`00E2', `KB_leftalt',                     `DV',    `keyboard left alt')dnl
ID(`00E3', `KB_left_GUI',                    `DV',    `keyboard left GUI')dnl
ID(`00E4', `KB_rightcontrol',                `DV',    `keyboard right control')dnl
ID(`00E5', `KB_rightshift',                  `DV',    `keyboard right shift')dnl
ID(`00E6', `KB_rightalt',                    `DV',    `keyboard right alt')dnl
ID(`00E7', `KB_right_GUI',                   `DV',    `keyboard right GUI')dnl
