Hidrd
=====

Hidrd is a library and a tool for reading, writing and converting HID report descriptors in/between various formats, with support as follows:

| Format                           | Reading | Writing |
| -------------------------------- | ------- | ------- |
| Native (binary)                  | Yes     | Yes     |
| XML                              | Yes     | Yes     |
| HID specification example format | No      | Yes     |
| C source code                    | No      | Yes     |

Hidrd contains `hidrd-convert` - a tool for converting report descriptors between formats. As it supports reading and writing XML, it is suitable for descriptor authoring and editing, on par with and in some ways better than the official [HID Descriptor Tool](http://www.usb.org/developers/hidpage#HID%20Descriptor%20Tool).

Advantages over the official tool include:
* running on *nix natively,
* reading native (binary) descriptors,
* smaller native descriptor output,
* non-interactive report descriptor generation, allowing for use in software/firmware builds.

Usage
-----

`hidrd-convert --help` output:

    Usage: hidrd-convert [OPTION]... [INPUT [OUTPUT]]
    Convert a HID report descriptor.
    With no INPUT, or when INPUT is -, read standard input.
    With no OUTPUT, or when OUTPUT is -, write standard output.

    Options:
      -h, --help                       this help message
      --hf, --help-formats             description of formats
                                       and their options
      -i, --input-format=FORMAT        use FORMAT for input
      --io=LIST, --input-options=LIST  use LIST input format options
      -o, --output-format=FORMAT       use FORMAT for output
      --oo=LIST, --output-options=LIST use LIST output format options

    Formats:

      natv [IO] - native
       xml [IO] - XML
      spec [ O] - specification example
      code [ O] - source code

    Default options are -i natv -o natv.

See `hidrd-convert --help-formats` for format options.


Examples
--------

Given a mouse report descriptor in binary (hex-dumped with `od -An -tx1`, revert with `xxd -r -p`):

     05 01 09 02 a1 01 09 01 a0 05 09 19 01 29 03 14
     25 01 75 01 95 03 81 02 75 05 95 01 81 01 05 01
     09 30 09 31 09 38 15 81 25 7f 75 08 95 03 81 06
     c0 c0

Use `hidrd-convert -o spec` to display it in the HID specification example format:

    Usage Page (Desktop),               ; Generic desktop controls (01h)
    Usage (Mouse),                      ; Mouse (02h, application collection)
    Collection (Application),
        Usage (Pointer),                ; Pointer (01h, physical collection)
        Collection (Physical),
            Usage Page (Button),        ; Button (09h)
            Usage Minimum (01h),
            Usage Maximum (03h),
            Logical Minimum (0),
            Logical Maximum (1),
            Report Size (1),
            Report Count (3),
            Input (Variable),
            Report Size (5),
            Report Count (1),
            Input (Constant),
            Usage Page (Desktop),       ; Generic desktop controls (01h)
            Usage (X),                  ; X (30h, dynamic value)
            Usage (Y),                  ; Y (31h, dynamic value)
            Usage (Wheel),              ; Wheel (38h, dynamic value)
            Logical Minimum (-127),
            Logical Maximum (127),
            Report Size (8),
            Report Count (3),
            Input (Variable, Relative),
        End Collection,
    End Collection

Convert it to XML with `hidrd-convert -o xml` (wrapped for readability):

    <?xml version="1.0"?>
    <descriptor xmlns="http://digimend.sourceforge.net"
                xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
                xsi:schemaLocation="http://digimend.sourceforge.net hidrd.xsd">
      <usage_page>desktop<!-- Generic desktop controls (01h) --></usage_page>
      <usage>desktop_mouse<!-- Mouse (02h, application collection) --></usage>
      <COLLECTION type="application">
        <usage>desktop_pointer<!-- Pointer (01h, physical collection) --></usage>
        <COLLECTION type="physical">
          <usage_page>button<!-- Button (09h) --></usage_page>
          <usage_minimum>01</usage_minimum>
          <usage_maximum>03</usage_maximum>
          <logical_minimum>0</logical_minimum>
          <logical_maximum>1</logical_maximum>
          <report_size>1</report_size>
          <report_count>3</report_count>
          <input>
            <variable/>
          </input>
          <report_size>5</report_size>
          <report_count>1</report_count>
          <input>
            <constant/>
          </input>
          <usage_page>desktop<!-- Generic desktop controls (01h) --></usage_page>
          <usage>desktop_x<!-- X (30h, dynamic value) --></usage>
          <usage>desktop_y<!-- Y (31h, dynamic value) --></usage>
          <usage>desktop_wheel<!-- Wheel (38h, dynamic value) --></usage>
          <logical_minimum>-127</logical_minimum>
          <logical_maximum>127</logical_maximum>
          <report_size>8</report_size>
          <report_count>3</report_count>
          <input>
            <variable/>
            <relative/>
          </input>
        </COLLECTION>
      </COLLECTION>
    </descriptor>

After editing (e.g. removing the wheel input), convert it back to binary with `hidrd-convert -i xml` (hex-dumped with `od -An -tx1`, revert with `xxd -r -p`):

     05 01 09 02 a1 01 09 01 a0 05 09 19 01 29 03 14
     25 01 75 01 95 03 81 02 75 05 95 01 81 01 05 01
     09 30 09 31 15 81 25 7f 75 08 95 02 81 06 c0 c0

Or use `hidrd-convert -i xml -o code` to produce C source code for the edited descriptor:

    0x05, 0x01, /*  Usage Page (Desktop),               */
    0x09, 0x02, /*  Usage (Mouse),                      */
    0xA1, 0x01, /*  Collection (Application),           */
    0x09, 0x01, /*      Usage (Pointer),                */
    0xA0,       /*      Collection (Physical),          */
    0x05, 0x09, /*          Usage Page (Button),        */
    0x19, 0x01, /*          Usage Minimum (01h),        */
    0x29, 0x03, /*          Usage Maximum (03h),        */
    0x14,       /*          Logical Minimum (0),        */
    0x25, 0x01, /*          Logical Maximum (1),        */
    0x75, 0x01, /*          Report Size (1),            */
    0x95, 0x03, /*          Report Count (3),           */
    0x81, 0x02, /*          Input (Variable),           */
    0x75, 0x05, /*          Report Size (5),            */
    0x95, 0x01, /*          Report Count (1),           */
    0x81, 0x01, /*          Input (Constant),           */
    0x05, 0x01, /*          Usage Page (Desktop),       */
    0x09, 0x30, /*          Usage (X),                  */
    0x09, 0x31, /*          Usage (Y),                  */
    0x15, 0x81, /*          Logical Minimum (-127),     */
    0x25, 0x7F, /*          Logical Maximum (127),      */
    0x75, 0x08, /*          Report Size (8),            */
    0x95, 0x02, /*          Report Count (2),           */
    0x81, 0x06, /*          Input (Variable, Relative), */
    0xC0,       /*      End Collection,                 */
    0xC0        /*  End Collection                      */

XML format
----------

Hidrd uses its own XML schema for report descriptors, as there is no standard. It is installed to `/usr/share/xml/schema/hidrd.xml` and is the definite reference to the XML format. The schema is generated from [lib/fmt/xml/hidrd.xsd.m4](https://github.com/DIGImend/hidrd/blob/master/lib/fmt/xml/hidrd.xsd.m4) during the build by substituting usage page and ID tokens. The template might be easier to navigate as it is much shorter. Still, it is a big schema, so a short introduction follows.

The root element of a descriptor is `descriptor`, and its contents are item or meta-item elements. Each item element correspond to a single report descriptor item (e.g. `usage`, `report_count`, `input`) and can have attributes or child elements describing their parameters (e.g. `collection` `type` attribute, or `input` flag elements). Most of the time, parameters are described with child elements. All item element names match the HID specification item names, only lowercased and having spaces replaced by underscores.

Meta-item elements have uppercase names and correspond to two report descriptor items - one for the opening and one for the closing tag. There are only three of them: `COLLECTION`, `PUSH` and `SET`. Each can be represented by a pair of item elements instead (`collection`/`end_collection`, `push`/`pop`, opening `delimiter` / closing `delimiter`). `COLLECTION` meta-item element has `type` attribute, similarly to `collection`. Meta-item elements are provided for convenience and can contain both item and meta-item elements.

Wherever a token value is accepted, such as for `COLLECTION` `type` attribute or `usage_page` element contents, a numeric value (either decimal or hexadecimal, but not both) is accepted as well. This is provided to support values not known to hidrd. See schema for details.

Arbitrary short and long items are supported as well, although not seen in practice. In fact, arbitrary binary stream should be representable with the schema, but hidrd doesn't support it at the moment.

Roadmap
-------

Hidrd development was stagnant for a long time, however some internal redesign should be made, particularly in error reporting. Next, perhaps, specification example input support should be implemented. Then validation needs to be cleaned up (bugs [#1](https://sourceforge.net/p/digimend/bugs/1/) and [#7](https://sourceforge.net/p/digimend/bugs/7/)).

After that, the time may come to implement a stream validation filter with recommendations from [HID Parser Error Checking](http://www.usb.org/developers/hidpage/hidpar.pdf).
