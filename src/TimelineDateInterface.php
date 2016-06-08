<?php

/**
 * Provides an interface for defining TimelineJS3 dates.
 */
interface TimelineDateInterface {

  /**
   * Formats a date for TimelineJS3.
   *
   * @return array
   *   An array representing a TimelineJS date object.
   */
  public function getTimelineDateArray();

}
