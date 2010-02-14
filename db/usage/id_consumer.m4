dnl
dnl Consumer usage page IDs.
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
ID(`0001',  `consumer_control',                 `CA',   `consumer control')dnl
ID(`0002',  `numeric_keypad',                   `NAry', `numeric key pad')dnl
ID(`0003',  `programmable_buttons',             `NAry', `programmable buttons')dnl
ID(`0004',  `microphone',                       `CA',   `microphone')dnl
ID(`0005',  `headphone',                        `CA',   `headphone')dnl
ID(`0006',  `graphic_equalizer',                `CA',   `graphic equalizer')dnl
ID(`0020',  `plus_10',                          `OSC',  `+10')dnl
ID(`0021',  `plus_100',                         `OSC',  `+100')dnl
ID(`0022',  `am_pm',                            `OSC',  `AM/PM')dnl
ID(`0030',  `power',                            `OOC',  `power')dnl
ID(`0031',  `reset',                            `OSC',  `reset')dnl
ID(`0032',  `sleep',                            `OSC',  `sleep')dnl
ID(`0033',  `sleep_after',                      `OSC',  `sleep after')dnl
ID(`0034',  `sleep_mode',                       `RTC',  `sleep mode')dnl
ID(`0035',  `illumination',                     `OOC',  `illumination')dnl
ID(`0036',  `function_buttons',                 `NAry', `function buttons')dnl
ID(`0040',  `menu',                             `OOC',  `menu')dnl
ID(`0041',  `menu_pick',                        `OSC',  `menu pick')dnl
ID(`0042',  `menu_up',                          `OSC',  `menu up')dnl
ID(`0043',  `menu_down',                        `OSC',  `menu down')dnl
ID(`0044',  `menu_left',                        `OSC',  `menu left')dnl
ID(`0045',  `menu_right',                       `OSC',  `menu right')dnl
ID(`0046',  `menu_escape',                      `OSC',  `menu escape')dnl
ID(`0047',  `menu_value_inc',                   `OSC',  `menu value increase')dnl
ID(`0048',  `menu_value_dec',                   `OSC',  `menu value decrease')dnl
ID(`0060',  `data_on_screen',                   `OOC',  `data on screen')dnl
ID(`0061',  `closed_caption',                   `OOC',  `closed caption')dnl
ID(`0062',  `closed_caption_select',            `OSC',  `closed caption select')dnl
ID(`0063',  `vcr_tv',                           `OOC',  `VCR/TV')dnl
ID(`0064',  `broadcast_mode',                   `OSC',  `broadcast mode')dnl
ID(`0065',  `snapshot',                         `OSC',  `snapshot')dnl
ID(`0066',  `still',                            `OSC',  `still')dnl
ID(`0080',  `selection',                        `NAry', `selection')dnl
ID(`0081',  `assign_selection',                 `OSC',  `assign selection')dnl
ID(`0082',  `mode_step',                        `OSC',  `mode step')dnl
ID(`0083',  `recall_last',                      `OSC',  `recall last')dnl
ID(`0084',  `enter_channel',                    `OSC',  `enter channel')dnl
ID(`0085',  `order_movie',                      `OSC',  `order movie')dnl
ID(`0086',  `channel',                          `LC',   `channel')dnl
ID(`0087',  `media_selection',                  `NAry', `media selection')dnl
ID(`0088',  `media_select_computer',            `Sel',  `media select computer')dnl
ID(`0089',  `media_select_tv',                  `Sel',  `media select TV')dnl
ID(`008A',  `media_select_www',                 `Sel',  `media select WWW')dnl
ID(`008B',  `media_select_dvd',                 `Sel',  `media select DVD')dnl
ID(`008C',  `media_select_telephone',           `Sel',  `media select telephone')dnl
ID(`008D',  `media_select_program_guide',       `Sel',  `media select program guide')dnl
ID(`008E',  `media_select_video_phone',         `Sel',  `media select video phone')dnl
ID(`008F',  `media_select_games',               `Sel',  `media select games')dnl
ID(`0090',  `media_select_messages',            `Sel',  `media select messages')dnl
ID(`0091',  `media_select_cd',                  `Sel',  `media select CD')dnl
ID(`0092',  `media_select_vcr',                 `Sel',  `media select VCR')dnl
ID(`0093',  `media_select_tuner',               `Sel',  `media select tuner')dnl
ID(`0094',  `quit',                             `OSC',  `quit')dnl
ID(`0095',  `help',                             `OOC',  `help')dnl
ID(`0096',  `media_select_tape',                `Sel',  `media select tape')dnl
ID(`0097',  `media_select_cable',               `Sel',  `media select cable')dnl
ID(`0098',  `media_select_satellite',           `Sel',  `media select satellite')dnl
ID(`0099',  `media_select_security',            `Sel',  `media select security')dnl
ID(`009A',  `media_select_home',                `Sel',  `media select home')dnl
ID(`009B',  `media_select_call',                `Sel',  `media select call')dnl
ID(`009C',  `channel_inc',                      `OSC',  `channel increment')dnl
ID(`009D',  `channel_dec',                      `OSC',  `channel decrement')dnl
ID(`009E',  `media_select_sap',                 `Sel',  `media select SAP')dnl
ID(`00A0',  `vcr_plus',                         `OSC',  `VCR plus')dnl
ID(`00A1',  `once',                             `OSC',  `once')dnl
ID(`00A2',  `daily',                            `OSC',  `daily')dnl
ID(`00A3',  `weekly',                           `OSC',  `weekly')dnl
ID(`00A4',  `monthly',                          `OSC',  `monthly')dnl
ID(`00B0',  `play',                             `OOC',  `play')dnl
ID(`00B1',  `pause',                            `OOC',  `pause')dnl
ID(`00B2',  `record',                           `OOC',  `record')dnl
ID(`00B3',  `fast_forward',                     `OOC',  `fast forward')dnl
ID(`00B4',  `rewind',                           `OOC',  `rewind')dnl
ID(`00B5',  `scan_next_track',                  `OSC',  `scan next track')dnl
ID(`00B6',  `scan_previous_track',              `OSC',  `scan previous track')dnl
ID(`00B7',  `stop',                             `OSC',  `stop')dnl
ID(`00B8',  `eject',                            `OSC',  `eject')dnl
ID(`00B9',  `random_play',                      `OOC',  `random play')dnl
ID(`00BA',  `select_disc',                      `NAry', `select disc')dnl
ID(`00BB',  `enter_disc',                       `MC',   `enter disc')dnl
ID(`00BC',  `repeat',                           `OSC',  `repeat')dnl
ID(`00BD',  `tracking',                         `LC',   `tracking')dnl
ID(`00BE',  `track_normal',                     `OSC',  `track normal')dnl
ID(`00BF',  `slow_tracking',                    `LC',   `slow tracking')dnl
ID(`00C0',  `frame_forward',                    `RTC',  `frame forward')dnl
ID(`00C1',  `frame_back',                       `RTC',  `frame back')dnl
ID(`00C2',  `mark',                             `OSC',  `mark')dnl
ID(`00C3',  `clear_mark',                       `OSC',  `clear mark')dnl
ID(`00C4',  `repeat_from_mark',                 `OOC',  `repeat from mark')dnl
ID(`00C5',  `return_to_mark',                   `OSC',  `return to mark')dnl
ID(`00C6',  `search_mark_forward',              `OSC',  `search mark forward')dnl
ID(`00C7',  `search_mark_backwards',            `OSC',  `search mark backwards')dnl
ID(`00C8',  `counter_reset',                    `OSC',  `Counter Reset')dnl
ID(`00C9',  `show_counter',                     `OSC',  `show counter')dnl
ID(`00CA',  `tracking_inc',                     `RTC',  `tracking increment')dnl
ID(`00CB',  `tracking_dec',                     `RTC',  `tracking decrement')dnl
ID(`00CC',  `stop_eject',                       `OSC',  `stop/eject')dnl
ID(`00CD',  `play_pause',                       `OSC',  `play/pause')dnl
ID(`00CE',  `play_skip',                        `OSC',  `play/skip')dnl
ID(`00E0',  `volume',                           `LC',   `volume')dnl
ID(`00E1',  `balance',                          `LC',   `balance')dnl
ID(`00E2',  `mute',                             `OOC',  `mute')dnl
ID(`00E3',  `bass',                             `LC',   `bass')dnl
ID(`00E4',  `treble',                           `LC',   `treble')dnl
ID(`00E5',  `bass_boost',                       `OOC',  `bass boost')dnl
ID(`00E6',  `surround_mode',                    `OSC',  `surround mode')dnl
ID(`00E7',  `loudness',                         `OOC',  `loudness')dnl
ID(`00E8',  `mpx',                              `OOC',  `MPX')dnl
ID(`00E9',  `volume_inc',                       `RTC',  `volume increment')dnl
ID(`00EA',  `volume_dec',                       `RTC',  `volume decrement')dnl
ID(`00F0',  `speed_select',                     `OSC',  `speed select')dnl
ID(`00F1',  `playback_speed',                   `NAry', `playback speed')dnl
ID(`00F2',  `standard_play',                    `Sel',  `standard play')dnl
ID(`00F3',  `long_play',                        `Sel',  `long play')dnl
ID(`00F4',  `extended_play',                    `Sel',  `extended play')dnl
ID(`00F5',  `slow',                             `OSC',  `slow')dnl
ID(`0100',  `fan_enable',                       `OOC',  `fan enable')dnl
ID(`0101',  `fan_speed',                        `LC',   `fan speed')dnl
ID(`0102',  `light_enable',                     `OOC',  `light enable')dnl
ID(`0103',  `light_illumination_level',         `LC',   `light illumination level')dnl
ID(`0104',  `climate_control_enable',           `OOC',  `climate control enable')dnl
ID(`0105',  `room_temperature',                 `LC',   `room temperature')dnl
ID(`0106',  `security_enable',                  `OOC',  `security enable')dnl
ID(`0107',  `fire_alarm',                       `OSC',  `fire alarm')dnl
ID(`0108',  `police_alarm',                     `OSC',  `police alarm')dnl
ID(`0109',  `proximity',                        `LC',   `proximity')dnl
ID(`010A',  `motion',                           `OSC',  `motion')dnl
ID(`010B',  `duress_alarm',                     `OSC',  `duress alarm')dnl
ID(`010C',  `holdup_alarm',                     `OSC',  `holdup alarm')dnl
ID(`010D',  `medical_alarm',                    `OSC',  `medical alarm')dnl
ID(`0150',  `balance_right',                    `RTC',  `balance right')dnl
ID(`0151',  `balance_left',                     `RTC',  `balance left')dnl
ID(`0152',  `bass_inc',                         `RTC',  `bass increment')dnl
ID(`0153',  `bass_dec',                         `RTC',  `bass decrement')dnl
ID(`0154',  `treble_inc',                       `RTC',  `treble increment')dnl
ID(`0155',  `treble_dec',                       `RTC',  `treble decrement')dnl
ID(`0160',  `speaker_system',                   `CL',   `speaker system')dnl
ID(`0161',  `channel_left',                     `CL',   `channel left')dnl
ID(`0162',  `channel_right',                    `CL',   `channel right')dnl
ID(`0163',  `channel_center',                   `CL',   `channel center')dnl
ID(`0164',  `channel_front',                    `CL',   `channel front')dnl
ID(`0165',  `channel_center_front',             `CL',   `channel center front')dnl
ID(`0166',  `channel_side',                     `CL',   `channel side')dnl
ID(`0167',  `channel_surround',                 `CL',   `channel surround')dnl
ID(`0168',  `channel_low_freq_enhan',           `CL',   `channel low frequency enhancement')dnl
ID(`0169',  `channel_top',                      `CL',   `channel top')dnl
ID(`016A',  `channel_unknown',                  `CL',   `channel unknown')dnl
ID(`0170',  `subchannel',                       `LC',   `sub-channel')dnl
ID(`0171',  `subchannel_inc',                   `OSC',  `sub-channel increment')dnl
ID(`0172',  `subchannel_dec',                   `OSC',  `sub-channel decrement')dnl
ID(`0173',  `alternate_audio_inc',              `OSC',  `alternate audio increment')dnl
ID(`0174',  `alternate_audio_dec',              `OSC',  `alternate audio decrement')dnl
ID(`0180',  `app_launch_buttons',               `NAry', `application launch buttons')dnl
ID(`0181',  `al_launch_button_config_tool',     `Sel',  `AL launch button configuration tool')dnl
ID(`0182',  `al_programmable_button_config',    `Sel',  `AL programmable button configuration')dnl
ID(`0183',  `al_consumer_control_config',       `Sel',  `AL consumer control configuration')dnl
ID(`0184',  `al_word_proc',                     `Sel',  `AL word processor')dnl
ID(`0185',  `al_text_editor',                   `Sel',  `AL text editor')dnl
ID(`0186',  `al_spreadsheet',                   `Sel',  `AL spreadsheet')dnl
ID(`0187',  `al_graphics_editor',               `Sel',  `AL graphics editor')dnl
ID(`0188',  `al_presentation_app',              `Sel',  `AL presentation app')dnl
ID(`0189',  `al_database_app',                  `Sel',  `AL database app')dnl
ID(`018A',  `al_email_reader',                  `Sel',  `AL email reader')dnl
ID(`018B',  `al_newsreader',                    `Sel',  `AL newsreader')dnl
ID(`018C',  `al_voicemail',                     `Sel',  `AL voicemail')dnl
ID(`018D',  `al_contacts_or_address_book',      `Sel',  `AL contacts/address book')dnl
ID(`018E',  `al_calendar_or_schedule',          `Sel',  `AL calendar/schedule')dnl
ID(`018F',  `al_task_or_project_mngr',          `Sel',  `AL task/project manager')dnl
ID(`0190',  `al_log_or_journal_or_timecard',    `Sel',  `AL log/journal/timecard')dnl
ID(`0191',  `al_checkbook_or_finance',          `Sel',  `AL checkbook/finance')dnl
ID(`0192',  `al_calculator',                    `Sel',  `AL calculator')dnl
ID(`0193',  `al_av_capture_or_playback',        `Sel',  `AL A/V capture/playback')dnl
ID(`0194',  `al_local_machine_brwsr',           `Sel',  `AL local machine browser')dnl
ID(`0195',  `al_lan_or_wan_brwsr',              `Sel',  `AL LAN/WAN browser')dnl
ID(`0196',  `al_internet_brwsr',                `Sel',  `AL Internet browser')dnl
ID(`0197',  `al_remote_net_or_isp_connect',     `Sel',  `AL remote networking/ISP connect')dnl
ID(`0198',  `al_network_conference',            `Sel',  `AL network conference')dnl
ID(`0199',  `al_network_chat',                  `Sel',  `AL network chat')dnl
ID(`019A',  `al_telephony_or_dialer',           `Sel',  `AL telephony/dialer')dnl
ID(`019B',  `al_logon',                         `Sel',  `AL logon')dnl
ID(`019C',  `al_logoff',                        `Sel',  `AL logoff')dnl
ID(`019D',  `al_logon_or_logoff',               `Sel',  `AL logon/logoff')dnl
ID(`019E',  `al_term_lock_or_screensaver',      `Sel',  `AL terminal lock/screensaver')dnl
ID(`019F',  `al_control_panel',                 `Sel',  `AL control panel')dnl
ID(`01A0',  `al_cmd_line_proc_or_run',          `Sel',  `AL command line processor/run')dnl
ID(`01A1',  `al_proc_or_task_mngr',             `Sel',  `AL process/task manager')dnl
ID(`01A2',  `al_select_task_or_app',            `Sel',  `AL select task/application')dnl
ID(`01A3',  `al_next_task_or_app',              `Sel',  `AL next task/application')dnl
ID(`01A4',  `al_previous_task_or_app',          `Sel',  `AL previous task/application')dnl
ID(`01A5',  `al_preemptive_halt_task_or_app',   `Sel',  `AL preemptive halt task/application')dnl
ID(`01A6',  `al_integrated_help_center',        `Sel',  `AL integrated help center')dnl
ID(`01A7',  `al_documents',                     `Sel',  `AL documents')dnl
ID(`01A8',  `al_thesaurus',                     `Sel',  `AL thesaurus')dnl
ID(`01A9',  `al_dictionary',                    `Sel',  `AL dictionary')dnl
ID(`01AA',  `al_desktop',                       `Sel',  `AL desktop')dnl
ID(`01AB',  `al_spell_check',                   `Sel',  `AL spell check')dnl
ID(`01AC',  `al_grammar_check',                 `Sel',  `AL grammar check')dnl
ID(`01AD',  `al_wireless_status',               `Sel',  `AL wireless status')dnl
ID(`01AE',  `al_keyboard_layout',               `Sel',  `AL keyboard layout')dnl
ID(`01AF',  `al_virus_protection',              `Sel',  `AL virus protection')dnl
ID(`01B0',  `al_encryption',                    `Sel',  `AL encryption')dnl
ID(`01B1',  `al_screen_saver',                  `Sel',  `AL screen saver')dnl
ID(`01B2',  `al_alarms',                        `Sel',  `AL alarms')dnl
ID(`01B3',  `al_clock',                         `Sel',  `AL clock')dnl
ID(`01B4',  `al_file_brwsr',                    `Sel',  `AL file browser')dnl
ID(`01B5',  `al_power_status',                  `Sel',  `AL power status')dnl
ID(`01B6',  `al_image_brwsr',                   `Sel',  `AL image browser')dnl
ID(`01B7',  `al_audio_brwsr',                   `Sel',  `AL audio browser')dnl
ID(`01B8',  `al_movie_brwsr',                   `Sel',  `AL movie browser')dnl
ID(`01B9',  `al_digital_rights_mngr',           `Sel',  `AL digital rights manager')dnl
ID(`01BA',  `al_digital_wallet',                `Sel',  `AL digital wallet')dnl
ID(`01BC',  `al_instant_messaging',             `Sel',  `AL instant messaging')dnl
ID(`01BD',  `al_oem_feats_brwsr',               `Sel',  `AL OEM features/tips/tutorial browser')dnl
ID(`01BE',  `al_oem_help',                      `Sel',  `AL OEM help')dnl
ID(`01BF',  `al_online_community',              `Sel',  `AL online community')dnl
ID(`01C0',  `al_ent_content_brwsr',             `Sel',  `AL entertainment content browser')dnl
ID(`01C1',  `al_online_shopping_brwsr',         `Sel',  `AL online shopping browser')dnl
ID(`01C2',  `al_smartcard_info_or_help',        `Sel',  `AL smartcard information/help')dnl
ID(`01C3',  `al_mrkt_mon_or_fin_brwsr',         `Sel',  `AL market monitor/finance browser')dnl
ID(`01C4',  `al_custom_corp_news_brwsr',        `Sel',  `AL customized corporate news browser')dnl
ID(`01C5',  `al_online_activity_brwsr',         `Sel',  `AL online activity browser')dnl
ID(`01C6',  `al_research_or_search_brwsr',      `Sel',  `AL research/search browser')dnl
ID(`01C7',  `al_audio_player',                  `Sel',  `AL audio player')dnl
ID(`0200',  `generic_gui_app_controls',         `Nary', `generic GUI application controls')dnl
ID(`0201',  `ac_new',                           `Sel',  `AC new')dnl
ID(`0202',  `ac_open',                          `Sel',  `AC open')dnl
ID(`0203',  `ac_close',                         `Sel',  `AC close')dnl
ID(`0204',  `ac_exit',                          `Sel',  `AC exit')dnl
ID(`0205',  `ac_maximize',                      `Sel',  `AC maximize')dnl
ID(`0206',  `ac_minimize',                      `Sel',  `AC minimize')dnl
ID(`0207',  `ac_save',                          `Sel',  `AC save')dnl
ID(`0208',  `ac_print',                         `Sel',  `AC print')dnl
ID(`0209',  `ac_properties',                    `Sel',  `AC properties')dnl
ID(`021A',  `ac_undo',                          `Sel',  `AC undo')dnl
ID(`021B',  `ac_copy',                          `Sel',  `AC copy')dnl
ID(`021C',  `ac_cut',                           `Sel',  `AC cut')dnl
ID(`021D',  `ac_paste',                         `Sel',  `AC paste')dnl
ID(`021E',  `ac_select_all',                    `Sel',  `AC select all')dnl
ID(`021F',  `ac_find',                          `Sel',  `AC find')dnl
ID(`0220',  `ac_find_and_replace',              `Sel',  `AC find and replace')dnl
ID(`0221',  `ac_search',                        `Sel',  `AC search')dnl
ID(`0222',  `ac_go_to',                         `Sel',  `AC go to')dnl
ID(`0223',  `ac_home',                          `Sel',  `AC home')dnl
ID(`0224',  `ac_back',                          `Sel',  `AC back')dnl
ID(`0225',  `ac_forward',                       `Sel',  `AC forward')dnl
ID(`0226',  `ac_stop',                          `Sel',  `AC stop')dnl
ID(`0227',  `ac_refresh',                       `Sel',  `AC refresh')dnl
ID(`0228',  `ac_previous_link',                 `Sel',  `AC previous link')dnl
ID(`0229',  `ac_next_link',                     `Sel',  `AC next link')dnl
ID(`022A',  `ac_bookmarks',                     `Sel',  `AC bookmarks')dnl
ID(`022B',  `ac_history',                       `Sel',  `AC history')dnl
ID(`022C',  `ac_subscriptions',                 `Sel',  `AC subscriptions')dnl
ID(`022D',  `ac_zoom_in',                       `Sel',  `AC zoom in')dnl
ID(`022E',  `ac_zoom_out',                      `Sel',  `AC zoom out')dnl
ID(`022F',  `ac_zoom',                          `LC',   `AC zoom')dnl
ID(`0230',  `ac_full_screen_view',              `Sel',  `AC full screen view')dnl
ID(`0231',  `ac_normal_view',                   `Sel',  `AC normal view')dnl
ID(`0232',  `ac_view_toggle',                   `Sel',  `AC view toggle')dnl
ID(`0233',  `ac_scroll_up',                     `Sel',  `AC scroll up')dnl
ID(`0234',  `ac_scroll_down',                   `Sel',  `AC scroll down')dnl
ID(`0235',  `ac_scroll',                        `LC',   `AC scroll')dnl
ID(`0236',  `ac_pan_left',                      `Sel',  `AC pan left')dnl
ID(`0237',  `ac_pan_right',                     `Sel',  `AC pan right')dnl
ID(`0238',  `ac_pan',                           `LC',   `AC pan')dnl
ID(`0239',  `ac_new_window',                    `Sel',  `AC new window')dnl
ID(`023A',  `ac_tile_horiz',                    `Sel',  `AC tile horizontally')dnl
ID(`023B',  `ac_tile_vert',                     `Sel',  `AC tile vertically')dnl
ID(`023C',  `ac_format',                        `Sel',  `AC format')dnl
ID(`023D',  `ac_edit',                          `Sel',  `AC edit')dnl
ID(`023E',  `ac_bold',                          `Sel',  `AC bold')dnl
ID(`023F',  `ac_italics',                       `Sel',  `AC italics')dnl
ID(`0240',  `ac_underline',                     `Sel',  `AC underline')dnl
ID(`0241',  `ac_strikethrough',                 `Sel',  `AC strikethrough')dnl
ID(`0242',  `ac_subscript',                     `Sel',  `AC subscript')dnl
ID(`0243',  `ac_superscript',                   `Sel',  `AC superscript')dnl
ID(`0244',  `ac_all_caps',                      `Sel',  `AC all caps')dnl
ID(`0245',  `ac_rotate',                        `Sel',  `AC rotate')dnl
ID(`0246',  `ac_resize',                        `Sel',  `AC resize')dnl
ID(`0247',  `ac_flip_horiz',                    `Sel',  `AC flip horizontal')dnl
ID(`0248',  `ac_flip_vert',                     `Sel',  `AC flip vertical')dnl
ID(`0249',  `ac_mirror_horiz',                  `Sel',  `AC mirror horizontal')dnl
ID(`024A',  `ac_mirror_vert',                   `Sel',  `AC mirror vertical')dnl
ID(`024B',  `ac_font_select',                   `Sel',  `AC font select')dnl
ID(`024C',  `ac_font_color',                    `Sel',  `AC font color')dnl
ID(`024D',  `ac_font_size',                     `Sel',  `AC font size')dnl
ID(`024E',  `ac_justify_left',                  `Sel',  `AC justify left')dnl
ID(`024F',  `ac_justify_center_h',              `Sel',  `AC justify center H')dnl
ID(`0250',  `ac_justify_right',                 `Sel',  `AC justify right')dnl
ID(`0251',  `ac_justify_block_h',               `Sel',  `AC justify block H')dnl
ID(`0252',  `ac_justify_top',                   `Sel',  `AC justify top')dnl
ID(`0253',  `ac_justify_center_v',              `Sel',  `AC justify center V')dnl
ID(`0254',  `ac_justify_bottom',                `Sel',  `AC justify bottom')dnl
ID(`0255',  `ac_justify_block_v',               `Sel',  `AC justify block V')dnl
ID(`0256',  `ac_indent_dec',                    `Sel',  `AC indent decrease')dnl
ID(`0257',  `ac_indent_inc',                    `Sel',  `AC indent increase')dnl
ID(`0258',  `ac_numbered_list',                 `Sel',  `AC numbered list')dnl
ID(`0259',  `ac_restart_numbering',             `Sel',  `AC restart numbering')dnl
ID(`025A',  `ac_bulleted_list',                 `Sel',  `AC bulleted list')dnl
ID(`025B',  `ac_promote',                       `Sel',  `AC promote')dnl
ID(`025C',  `ac_demote',                        `Sel',  `AC demote')dnl
ID(`025D',  `ac_yes',                           `Sel',  `AC yes')dnl
ID(`025E',  `ac_no',                            `Sel',  `AC no')dnl
ID(`025F',  `ac_cancel',                        `Sel',  `AC cancel')dnl
ID(`0260',  `ac_catalog',                       `Sel',  `AC catalog')dnl
ID(`0261',  `ac_buy_or_checkout',               `Sel',  `AC buy/checkout')dnl
ID(`0262',  `ac_add_to_cart',                   `Sel',  `AC add to cart')dnl
ID(`0263',  `ac_expand',                        `Sel',  `AC expand')dnl
ID(`0264',  `ac_expand_all',                    `Sel',  `AC expand all')dnl
ID(`0265',  `ac_collapse',                      `Sel',  `AC collapse')dnl
ID(`0266',  `ac_collapse_all',                  `Sel',  `AC collapse all')dnl
ID(`0267',  `ac_print_preview',                 `Sel',  `AC print preview')dnl
ID(`0268',  `ac_paste_special',                 `Sel',  `AC paste special')dnl
ID(`0269',  `ac_insert_mode',                   `Sel',  `AC insert mode')dnl
ID(`026A',  `ac_delete',                        `Sel',  `AC delete')dnl
ID(`026B',  `ac_lock',                          `Sel',  `AC lock')dnl
ID(`026C',  `ac_unlock',                        `Sel',  `AC unlock')dnl
ID(`026D',  `ac_protect',                       `Sel',  `AC protect')dnl
ID(`026E',  `ac_unprotect',                     `Sel',  `AC unprotect')dnl
ID(`026F',  `ac_attach_comment',                `Sel',  `AC attach comment')dnl
ID(`0270',  `ac_delete_comment',                `Sel',  `AC delete comment')dnl
ID(`0271',  `ac_view_comment',                  `Sel',  `AC view comment')dnl
ID(`0272',  `ac_select_word',                   `Sel',  `AC select word')dnl
ID(`0273',  `ac_select_sentence',               `Sel',  `AC select sentence')dnl
ID(`0274',  `ac_select_paragraph',              `Sel',  `AC select paragraph')dnl
ID(`0275',  `ac_select_column',                 `Sel',  `AC select column')dnl
ID(`0276',  `ac_select_row',                    `Sel',  `AC select row')dnl
ID(`0277',  `ac_select_table',                  `Sel',  `AC select table')dnl
ID(`0278',  `ac_select_object',                 `Sel',  `AC select object')dnl
ID(`0279',  `ac_redo_or_repeat',                `Sel',  `AC redo/repeat')dnl
ID(`027A',  `ac_sort',                          `Sel',  `AC sort')dnl
ID(`027B',  `ac_sort_ascending',                `Sel',  `AC sort ascending')dnl
ID(`027C',  `ac_sort_descending',               `Sel',  `AC sort descending')dnl
ID(`027D',  `ac_filter',                        `Sel',  `AC filter')dnl
ID(`027E',  `ac_set_clock',                     `Sel',  `AC set clock')dnl
ID(`027F',  `ac_view_clock',                    `Sel',  `AC view clock')dnl
ID(`0280',  `ac_select_time_zone',              `Sel',  `AC select time zone')dnl
ID(`0281',  `ac_edit_time_zones',               `Sel',  `AC edit time zones')dnl
ID(`0282',  `ac_set_alarm',                     `Sel',  `AC set alarm')dnl
ID(`0283',  `ac_clear_alarm',                   `Sel',  `AC clear alarm')dnl
ID(`0284',  `ac_snooze_alarm',                  `Sel',  `AC snooze alarm')dnl
ID(`0285',  `ac_reset_alarm',                   `Sel',  `AC reset alarm')dnl
ID(`0286',  `ac_synchronize',                   `Sel',  `AC synchronize')dnl
ID(`0287',  `ac_send_or_receive',               `Sel',  `AC send/receive')dnl
ID(`0288',  `ac_send_to',                       `Sel',  `AC send to')dnl
ID(`0289',  `ac_reply',                         `Sel',  `AC reply')dnl
ID(`028A',  `ac_reply_all',                     `Sel',  `AC reply all')dnl
ID(`028B',  `ac_forward_msg',                   `Sel',  `AC forward msg')dnl
ID(`028C',  `ac_send',                          `Sel',  `AC send')dnl
ID(`028D',  `ac_attach_file',                   `Sel',  `AC attach file')dnl
ID(`028E',  `ac_upload',                        `Sel',  `AC upload')dnl
ID(`028F',  `ac_download_and_save_as',          `Sel',  ``AC download (save target as)'')dnl
ID(`0290',  `ac_set_borders',                   `Sel',  `AC set borders')dnl
ID(`0291',  `ac_insert_row',                    `Sel',  `AC insert row')dnl
ID(`0292',  `ac_insert_column',                 `Sel',  `AC insert column')dnl
ID(`0293',  `ac_insert_file',                   `Sel',  `AC insert file')dnl
ID(`0294',  `ac_insert_picture',                `Sel',  `AC insert picture')dnl
ID(`0295',  `ac_insert_object',                 `Sel',  `AC insert object')dnl
ID(`0296',  `ac_insert_symbol',                 `Sel',  `AC insert symbol')dnl
ID(`0297',  `ac_save_and_close',                `Sel',  `AC save and close')dnl
ID(`0298',  `ac_rename',                        `Sel',  `AC rename')dnl
ID(`0299',  `ac_merge',                         `Sel',  `AC merge')dnl
ID(`029A',  `ac_split',                         `Sel',  `AC split')dnl
ID(`029B',  `ac_disribute_horiz',               `Sel',  `AC disribute horizontally')dnl
ID(`029C',  `ac_distribute_vert',               `Sel',  `AC distribute vertically')dnl
