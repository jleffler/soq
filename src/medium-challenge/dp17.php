<?php
function distinctPowers($min, $max) {
 $numbers = [];
 
 for ($i = $min; $i <= $max; $i++) {
  for ($j = $min; $j <= $max; $j++) {  
   $numbers[] = pow($i, $j);
  }
 }
 
 $unique_numbers = array_unique($numbers);
 sort($unique_numbers);
 
 return $unique_numbers;
}
echo print_r(distinctPowers(2, 5), 1); // [4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125]
echo print_r(count(distinctPowers(2, 100)), 1); // 9183 distinct terms
echo print_r(distinctPowers(2, 100), 1); // 9183 distinct terms
?>
