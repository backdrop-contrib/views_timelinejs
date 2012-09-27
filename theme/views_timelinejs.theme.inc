<?php

/**
 * Preprocess function for views-timelinejs.tpl.php
 */
function template_preprocess_views_timelinejs(&$vars) {
  global $language;

  // Load required libraries and styles
  views_timelinejs_load_libraries();

  $view = $vars['view'];
  $vars['timelinejs_id'] = 'timelinejs_' . $view->name . '_' . $view->current_display;

  $settings = array(
    'width' => '100%',
    'height' => '500',
    'source' => $vars['rows'],
    'embed_id' => $vars['timelinejs_id'],
    'lang' => $language->language,
  );

  // Include inline javascript
  drupal_add_js(array('timelineJS' => $settings), 'setting');
  drupal_add_js(drupal_get_path('module', 'views_timelinejs') . '/js/views_timelinejs.js');

}
