<?php
/**
 * @file
 *
 */



/**
 * abstract class step
 *  Base class which should not be called directly,
 *
 *  The class contains three methods:
 *  - __construct
 *  - public get_intent()
 *  - public parse_intent()
 */

abstract class step {
  protected $intent;
  
  /**
   * @return string
   */
  abstract public function get_intent();

  /**
   * @return casperjs code as string
   *
   */
  abstract public function parse_intent()
    
}