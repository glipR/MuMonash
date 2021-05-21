# Emiles pictures are just pictures of smaller and smaller regions containing eachother, due to constraint 3.
# [[[[[]]]]]
# Actually moving this concentric circles into the right spot is a bit of implementation hell though.
# A recursive argument should work: if replacing this bit will break a chain in a smaller circle, then we need to patch it up by placing some specific bits first, so solve for the smaller circles.
# 32 iterations per bit placement on 64*103 sized grid <= 250000 bit flips, so small enough.
