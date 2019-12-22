<?php
function KaprekarsConstant($number, $numberOfIterations = 1) {
  $number = (string) $number;
  
  if (strlen($number) < 4) {
    for ($i = strlen($number); $i < 4; $i++) {
      $number .= '0';
    }
  }
  
  $asc = str_split($number);
  $desc = $asc;
  
  rsort($desc);
  sort($asc);
  
  $asc_number = (int) implode($asc, '');
  $desc_number = (int) implode($desc, '');
  $difference = abs($asc_number - $desc_number);
  
  if ($difference !== 6174) {
    return KaprekarsConstant($difference, $numberOfIterations + 1);
  }
  
  return $numberOfIterations; 
}
echo KaprekarsConstant(2111); // 5
echo KaprekarsConstant(9831); // 7
?>
