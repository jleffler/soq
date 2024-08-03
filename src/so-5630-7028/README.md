### Stack Overflow Question 5630-7028

[SO 5630-7028](https://stackoverflow.com/q/56307028) &mdash;
Which case(s) are not covered in this code for calculating the area
covered by possibly overlapping rectangles?

The question is about the total area of possibly overlapping rectangles
defined by bottom-left and top-right coordinates.

(See: [Rectilinear Polgygon](https://en.wikipedia.org/wiki/Rectilinear_polygon)

Various bits of code, including structures in some.

* `overlap61.c` - code from the question, reformatted
* `overlap47.c` - revised code from question avoiding floating point arithmetic
* `overlap73.c` - rewritten code using structures as well as separate coordinates
* `overlap31.c` - revised version of `overlap73.c` using `long long` to
   avoid integer arithmetic overflows

None of this was posted to SO.
