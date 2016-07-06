# http://stackoverflow.com/questions/15442950/calling-different-programs-with-different-options
GETOPT=/usr/gnu/bin/getopt

args=$($GETOPT -o :v -l prog1:,prog2: -- "$@")
eval set -- "$args"
while [ $# -gt 0 ]
do
    case $1 in
          -v ) echo "VERBOSE"; shift;;
     --prog1 )
               echo "prog1 has been chosen with the following options: $2"
               opts1="$2"
               shift 2;;
     --prog2 )
               echo "prog2 has been chosen with the following options: $2"
               opts2="$2"
               shift 2;;
          -- )
               shift; break;;
           * ) echo "$0: oops! $1 unexpected" >&2; exit 1;;
    esac
done
echo "$0: residual arguments: $@"

if [ -n "$opts1" ]
then
     args=$($GETOPT -o d:BR:S: -- $opts1)
     eval set -- "$args"
     while [ $# -gt 0 ]
     do
         case $1 in
         -d )  echo "prog1 -d:$2"; shift 2;;
         -B )  echo "prog1 -B";    shift 1;;
         -R )  echo "prog1 -R:$2"; shift 2;;
         -S )  echo "prog1 -S:$2"; shift 2;;
         -- )  shift; break;;
          * )  echo "$0: oops processing prog1 - $1 unexpected" >&2; exit 1;;
         esac
     done
     echo "prog1 opts -- $@"
     # Now execute prog1?
fi

if [ -n "$opts2" ]
then
     args=$($GETOPT -o f:AT:G: -- $opts2)
     eval set -- "$args"
     while [ $# -gt 0 ]
     do
         case $1 in
         -f )  echo "prog2 -f:$2"; shift 2;;
         -A )  echo "prog2 -A";    shift 1;;
         -T )  echo "prog2 -T:$2"; shift 2;;
         -G )  echo "prog2 -G:$2"; shift 2;;
         -- )  shift; break;;
          * )  echo "$0: oops processing prog2 - $1 unexpected" >&2; exit 1;;
         esac
     done
     echo "prog2 opts -- $@"
     # Now execute prog2?
fi

