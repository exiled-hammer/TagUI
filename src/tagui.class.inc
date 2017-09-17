<?php

/**
 * @file 
 *   Factory class for parsing Tagui
 *   
 */

class tagui {
  public $driver;
  public $classes;
  
  function __construct($driver) {
    $this->driver = $driver;
    $this->getClasses();
  }
  
  protected function getClasses() {
    $directories['core']     = 'steps/core/' . $this->driver;
    $directories['custom']   = 'steps/custom/' . $this->driver;
    
    foreach ($directories as $directory) {
      foreach (new DirectoryIterator($directory) as $fileInfo) {
        // ignore dot files
        if($fileInfo->isDot()) continue;
        $matches = array();
        if (preg_match('/^(?<class>[^.].+)\.class.inc$/', $fileInfo->getFilename(), $matches)) {
          $class= $matches['class'];
          $this->classes[$class] = $fileInfo->getPathname();        
        }
      }
    }
  }
  
  protected function loadSteps() {
    foreach ($this->classes as $class => $path) {
      include_once($path);
      $this->steps->{$step} = new $step();
    }
  }

  
}