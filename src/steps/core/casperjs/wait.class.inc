<?php
/**
 * @file
 *
 */

/**
 *  wait class which is a child of step
 *  The class contains two methods:
 *  - public get_intent()
 *  - public parse_intent()
 */

class wait extends step {  
  /**
   * Construct wrapper object   
   */
  public function __construct($intent){    
    $this->intent = $intent;
  }
  
  /**
   * @return string
   */
  public function get_intent($intent) {
    if (substr($intent, 0, 5) == "wait " || $intent == "wait") {
      return "wait";
    }
    return FALSE;
  }

  /**
   * @return string 
   *   casperjs code as string
   *
   * @param string $raw_intent
   *   The full written step line for passing directly to the casperjs output or parsing for sikuli
   * @param array $params
   *   Array of params for the given step
   * @param string $twb
   *   Tagui_web_browser token for constructing test header casperjs   
   * @param boolean $sikuli
   *   if input is meant for sikuli visual automation 
   *
   */
  public function parse_intent($raw_intent) {     
    // wait is a new block, invalid to use after frame, thus skip end_fi()
    $params = trim(substr($raw_intent." ",1+strpos($raw_intent." "," "))); if ($params == "") $params = "5";
    if ($GLOBALS['inside_frame']!=0) echo "ERROR - " . current_line() . " invalid after frame - " . $raw_intent . "\n";
    else if ($GLOBALS['inside_popup']!=0) echo "ERROR - " . current_line() . " invalid after popup - " . $raw_intent . "\n";
    else return "techo('".$raw_intent."');});\n\ncasper.wait(" . (floatval($params)*1000) . ", function() {\n";
  }
}
// notes from GUS
// The above depends on the assumption that the checking of $params not being empty happens before the call to the parse_intent() method
// same goes for the sikuli check and establishing $twb.



/*  copying in the original php function from tagui_parse.php for john to review oop version.

function wait_intent($raw_intent) { 
  // wait is a new block, invalid to use after frame, thus skip end_fi()
  $params = trim(substr($raw_intent." ",1+strpos($raw_intent." "," "))); if ($params == "") $params = "5";
  if ($GLOBALS['inside_frame']!=0) echo "ERROR - " . current_line() . " invalid after frame - " . $raw_intent . "\n";
  else if ($GLOBALS['inside_popup']!=0) echo "ERROR - " . current_line() . " invalid after popup - " . $raw_intent . "\n";
  else return "techo('".$raw_intent."');});\n\ncasper.wait(" . (floatval($params)*1000) . ", function() {\n";
}




*/