<?php
/**
 * @file
 * Text field integration as a tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Taxonomy Term Reference field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'taxonomy_term_reference',
  'callback' => 'views_timelinejs_taxonomy_term_reference_tag',
);

function views_timelinejs_taxonomy_term_reference_tag($value, $options = array()) {
  if (isset($value['tid']) && $value['tid'] != '') {
    $tid = $value['tid'];
    $term = taxonomy_term_load($tid);

    return $term->name;
  }
  else {
    return false;
  }
}