Image
=====

Because I didn't use OpenCV, images are stored in a non-standardized
format, which is described here:

* 32 bit int specifying width
* 32 bit int specifying height
* ``width * height * 3`` bytes, each corresponding to a channel value.

Endianness is dependent on your machine.

You can use the script ``scripts/imgconv.py`` to convert between ``.qif``
and another format.
