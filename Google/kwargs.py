def print_kwargs(**kwargs):
  for k in kwargs:
    print k, " => ", kwargs[k]

def kwargs_demo(a, **kwargs):
  print a
  print_kwargs(**kwargs)

kwargs_demo(1)
kwargs_demo(99, **{'cat':'dog', 'ice':'cream'})

# def kwargs_mark2(a):
#   print a
#   other = None
#   print_kwargs(**other)
#
# kwargs_mark2(24)
#
# Generates runtime error:
# Traceback (most recent call last):
#     File "kwargs.py", line 17, in <module>
#         kwargs_mark2(24)
#     File "kwargs.py", line 15, in kwargs_mark2
#         print_kwargs(**other)
# TypeError: print_kwargs() argument after ** must be a mapping, not NoneType

def kwargs_mark3(a):
  print a
  other = {}
  print_kwargs(**other)

kwargs_mark3(24)
