<?php

/**
 * Defines a TimelineJS3 title slide.
 */
class TimelineTitleSlide extends TimelineSlide {

  public function __construct(TimelineTextInterface $text = NULL) {
    if (!empty($text)) {
      $this->text = $text;
    }
  }

}
