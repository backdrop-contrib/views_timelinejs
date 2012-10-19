<?php

/**
 * @file
 * Defines the View Style Plugins for Views TimelineJS module.
 */

/**
 * Implements hook_views_plugins().
 */
function views_timelinejs_views_plugins() {
  $path = drupal_get_path('module', 'views_timelinejs') . '/views';
  return array(
    'style' => array(
      'timelinejs' => array(
        'title' => t('TimelineJS'),
        'help' => t('Display the results in a Timeline.'),
        'handler' => 'views_timelinejs_plugin_style_timelinejs',
        'uses options' => TRUE,
        'uses row plugin' => FALSE,
        'uses grouping' => FALSE,
        'uses fields'     => TRUE,
        'uses row class' => FALSE,
        'type' => 'normal',
        'path' => $path . '/plugins',
        'theme' => 'views_timelinejs',
        'theme path' => $path . '/theme',
        'theme file' => 'views_timelinejs.theme.inc',
      ),
    ),
  );
}
