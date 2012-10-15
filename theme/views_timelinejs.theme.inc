<?php

/**
 * Preprocess function for views-timelinejs.tpl.php
 */
function template_preprocess_views_timelinejs(&$vars) {
  // Load required libraries and styles
  views_timelinejs_load_libraries();

  // Include inline javascript
  drupal_add_js(array('timelineJS' => $vars['timelinejs']), 'setting');
  drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');
}

/**
 * Theme function to add Read more link after timeline entry bodytext
 */
function theme_views_timelinejs_link_to_entity($vars) {
  return '<p class="read-more">' . l($vars['link_text'], $vars['uri']) . '</p>';
}
