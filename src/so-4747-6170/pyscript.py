import fileinput


output_files = {}
#with open(file) as fh:
#    for line in fh:
for line in fileinput.input():
    cols = line.strip().split()
    prefix = cols[1][0:3]
    # Cache the output file handles, so that each is opened only once.
    #outfh = output_files.setdefault(prefix, open("../split_DB/{}.part".format(prefix), "w"))
    outfh = output_files.setdefault(prefix, open("split_DB/{}.part".format(prefix), "w"))
    print(line, file=outfh)

# Close all the output files
for f in output_files.values():
    f.close()
