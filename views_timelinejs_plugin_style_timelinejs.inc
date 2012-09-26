<?php

/**
 * @file
 */

/**
 * This class holds all the funtionality used for the unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  function option_definition() {
    // TODO: Define all plugin settings here
    $options = array(
      'timeline_fields' => array(
        'headline' => array('default' => '', 'translatable' => FALSE),
        'bodytext' => array('default' => '', 'translatable' => FALSE),
        'media' => array('default' => '', 'translatable' => FALSE),
        'date' => array('default' => '', 'translatable' => FALSE),
      ),
    );
    return array_merge(parent::option_definition(), $options);
  }

  function options_form(&$form, &$form_state) {
    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure TimelineJS.') . '</div>',
      );
      return;
    }

    $options = $this->display->handler->get_field_labels();
    $fields = $this->display->handler->get_option('fields');

    $text_fields = array('0' => t('None'));
    $date_fields = array();
    $media_fields = array();

    foreach($fields as $field) {
      $text_fields[$field['id']] = $options[$field['id']];
    }

    // TODO: Detect field types, populate only compatible fields
    $date_fields = $text_fields;
    $media_fields = $text_fields;

    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for headline',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['headline']) ? $this->options['timeline_fields']['headline'] : '',
    );
    $form['timeline_fields']['bodytext'] = array(
      '#type' => 'select',
      '#options' => $text_fields,
      '#title' => 'Select field for bodytext',
      '#description' => t('This field should be a text-like field'),
      '#default_value' => isset($this->options['timeline_fields']['bodytext']) ? $this->options['timeline_fields']['bodytext'] : '',
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $media_fields,
      '#title' => 'Select field for media asset',
      '#description' => t('Only image fields are currently supported'),
      '#default_value' => isset($this->options['timeline_fields']['media']) ? $this->options['timeline_fields']['media'] : '',
    );
    $form['timeline_fields']['date'] = array(
      '#type' => 'select',
      '#options' => $date_fields,
      '#title' => 'Select field for date element',
      '#description' => t('Only UNIX timestamp-like date fields are currently supported (node created, updated, etc...)'),
      '#default_value' => isset($this->options['timeline_fields']['date']) ? $this->options['timeline_fields']['date'] : '',
    );

  }

  /**
   * Render the display in this style.
   */
  function render() {
    $view = $this->view;

    $field_mapping = array(
      'startDate' => 'date',
      'endDate' => 'date',
      'headline' => 'headline',
      'text' => 'bodytext',
      'media' => 'media',
    );

    $rows = array();
    $media_field_type = isset($this->options['timeline_fields']['media']) ? $view->field[$this->options['timeline_fields']['media']]->field_info['type'] : NULL;

    // TODO: Should we skip parsing Views results entirely, if this is not the JSON output
    // Build a TimelineJS friendly array from the views data
    foreach($this->view->result as $count => $row) {
      $fields = array();

      // Get basic data for each timeline entry field based on display handler settings
      foreach($field_mapping as $target_field => $source_field) {
        if(isset($this->options['timeline_fields'][$source_field])) {
          // Get field alias, so we can check agains $row if all fields have data
          $field_alias = $view->field[$this->options['timeline_fields'][$source_field]]->field_alias;
          if(isset($row->$field_alias)) {
            if(is_array($row->$field_alias) && !count($row->$field_alias)) {
              // The field data is propably empty, prevent from executing get_field_value()
            }
            else {
              // Get field's raw value
              $fields[$target_field] = $this->view->style_plugin->get_field_value($count, $this->options['timeline_fields'][$source_field]);
            }
          }
        }
      }

      // Apply additional field-level processing
      if(isset($fields['startDate'])) {
        $fields['startDate'] = format_date($fields['startDate'], 'custom', 'Y,m,d');
      }
      if(isset($fields['endDate'])) {
        $fields['endDate'] = format_date($fields['endDate'], 'custom', 'Y,m,d');
      }
      if(isset($fields['media']) && is_array($fields['media'])) {
        $field_tmp = array_shift($fields['media']);
        if(isset($field_tmp['uri'])) {
          $fields['media'] = file_create_url($field_tmp['uri']);
        }
      }

      // Loop through fields if there are arrays and deassemble them to get value
      foreach($fields as $name => $field) {
        if(is_array($field)) {
          $field_tmp = array_shift($field);
          $fields[$name] = $field_tmp['value'];
        }

        // Sanitize all user inputted output
        $fields[$name] = check_plain($fields[$name]);
      }

      // Combine the results array with processed row data
      $rows[$count]['startDate'] = isset($fields['startDate']) ? $fields['startDate'] : '';
      $rows[$count]['endDate'] = isset($fields['endDate']) ? $fields['endDate'] : '';
      $rows[$count]['headline'] = isset($fields['headline']) ? $fields['headline'] : '';
      $rows[$count]['text'] = isset($fields['text']) ? $fields['text'] : '';
      $rows[$count]['asset']['media'] = isset($fields['media']) ? $fields['media'] : '';
    }

    // Skip rendering if view is being edited or previewed
    if(!$view->editing) {
      if(isset($this->view->json)) {
        // Output results as JSON data to feed TimelineJS library
        $data = array(
          'timeline' => array(
            'headline' => 'Title',
            'type' => 'default',
            'date' => $rows,
          ),
        );
        return drupal_json_encode($data);
      }
      else {
        // Output wrapper markup and include JS libraries
        return theme('views_timelinejs', array('view' => $view, 'options' => $this->options, 'rows' => $rows));
      }
    }
   else {
      return t('TimelineJS style does not support preview mode.');
    }
  }
}