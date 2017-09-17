<?php
/**
 * @file
 *
 */

/**
 *  url class which is a child of step
 *  The class contains two methods:
 *  - public get_intent()
 *  - public parse_intent()
 */

class url extends step {  
  /**
   * Construct wrapper object   
   */
  public function __construct(){    
    $this->intent = __CLASS__;
  }
  /**
   * @return string
   */
  public function get_intent($intent) {    
    
    if ((substr($intent,0,7)=="http://") || (substr($intent,0,8)=="https://")) {
      return TRUE;
    }
    
    return FALSE;
  }

  /**
   * @return string 
   *   casperjs code as string
   *
   * @param array $params
   *   Array of params for the given step
   * @param string $twb
   *   Tagui_web_browser token for constructing test header casperjs   
   * @param boolean $sikuli
   *   if input is meant for sikuli visual automation 
   *
   */
  public function parse_intent(array $params, $twb, $sikuli) {     
    if ($twb == 'chrome'){
      $casper_url = 'about:blank'; $chrome_call = "chrome_step('Page.navigate',{url: '".$this->intent."'}); sleep(1000);\n";
    }
    // check if dynamic url is used
    if (strpos($this->intent,"'+")!==false and strpos($this->intent,"+'")!==false) {
      // wrap step within casper context if variable (casper context) is used in url, in order to access variable
      $dynamic_header = "\n{casper.then(function() {\n"; $dynamic_footer = "})} // end of dynamic url block\n";
    }
    else {
      $dynamic_header = ""; $dynamic_footer = ""; // else casper.start/thenOpen can be outside casper context
      if (filter_var($this->intent, FILTER_VALIDATE_URL) == false) // do url validation only for raw text url string
      echo "ERROR - " . current_line() . " invalid URL " . $this->intent . "\n";
    }
    if ($GLOBALS['line_number'] == 1) { 
      // use casper.start for first URL call and casper.thenOpen for subsequent calls
      $GLOBALS['url_provided']=true; return $dynamic_header."casper.start('".$casper_url."', function() {\n".$chrome_call."techo('".$this->intent."' + ' - ' + ".$twb.".getTitle() + '\\n');});\n\ncasper.then(function() {\n".$dynamic_footer;
    }
    else {
      return $dynamic_header."});casper.thenOpen('".$casper_url."', function() {\n".$chrome_call."techo('".$this->intent."' + ' - ' + ".$twb.".getTitle());});\n\ncasper.then(function() {\n".$dynamic_footer;
    }
  }
}                 