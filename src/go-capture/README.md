# Go Capture

In the ancient Chinese and Japanese board game of Go, there are two
colours of stones, black and white, played on a square board with an odd
number of grid lines.
In this context, 9x9, 11x11, 13x13, 15x15, 17x17, 19x19 boards are
allowed.
Stones are played on the intersections of grid lines.

In the game, players take it in turns to play, black playing first.
Stones are captured when they have no liberties left.
Liberties are empty spaces along the lines of a grid; diagonals do not
count, and neither do edges.
Stones in a corner have at most two liberties; stones on the edge have
at most three liberties; stones in the middle can have four liberties.
Groups of stones are formed when two stones of the same colour touch
along a grid line.

At any time, a stone can be played on any empty intersection, unless the
stone would be captured after the move is complete.
However, if the play would capture some of the opponents stones, those
are removed before the turn is over, so it is possible to capture
stones.

If a group has two eyes (holes in the middle), then the stones cannot be
captured because to do so, the opponent would have play two stones in a
position where they would be captured, but they can't do that because
you only get to play one stone in a turn.

The exercise is to detect which stones on a board layout are captured.
It has to read the board, rejecting invalid layouts.  It has to analyze
each stone on the board to detect those which are captured.

