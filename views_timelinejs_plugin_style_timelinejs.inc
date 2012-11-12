<?php

/**
 * @file
 */

/**
 * This class holds all the funtionality used for the unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /*
   * REMOVED OPTIONS_DEFINITION FOR NOW.
   *
  function option_definition() {
    // TODO: Define all plugin settings here
    $options = array(
      'timeline_fields' => array(
        'headline' => array('default' => '', 'translatable' => FALSE),
        'bodytext' => array('default' => '', 'translatable' => FALSE),
        'media' => array('default' => '', 'translatable' => FALSE),
        'date' => array('default' => '', 'translatable' => FALSE),
      ),
      'timeline_config' => array(
        'link_to_entity' => array('default' => '', 'translatable' => FALSE),
        'link_text_enabled' => array('default' => '', 'translatable' => FALSE),
        'link_text' => array('default' => '', 'translatable' => FALSE),
      ),
    );
    return array_merge(parent::option_definition(), $options);
  }
   */

  function options_form(&$form, &$form_state) {

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#prefix' => '<div class="error messages">',
        '#markup' => t('You need at least one field before you can configure TimelineJS.'),
        '#suffix' => '</div>',
      );
      return;
    }

    $options = $this->display->handler->get_field_labels();
    $media_fields = array('0' => t('None'));
    $date_fields = array('0' => t('None'));
    $text_fields = array('0' => t('None'));

    // Load all date_source plugins.
    ctools_include('plugins');
    $date_sources = ctools_get_plugins('views_timelinejs', 'date_sources');
    $text_sources = ctools_get_plugins('views_timelinejs', 'text_sources');
    $media_sources = ctools_get_plugins('views_timelinejs', 'media_sources');

    // Go through all the field handlers to check support.
    foreach ($handlers as $field => $handler) {
      // Get a nice name for the field.
      $field_names[$field] = $handler->ui_name();
      if ($label = $handler->label()) {
        $field_names[$field] .= ' ("' . $label . '")';
      }

      if (isset($handler->definition['field_name'])) {
        $field_name = $handler->definition['field_name'];
        $field_info = field_info_field($field_name);
      }

      // Check if field is supported as a date source.
      foreach ($date_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ($field_info['type'] == $source['field_type'] || $field == 'created' || $field == 'changed') {
            $date_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported text source.
      foreach($text_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if ((isset($field_info['type']) && $field_info['type'] == $source['field_type']) || $field == 'title') {
            $text_fields[$field] = $field_names[$field];
          }
        }
      }

      // Check if field is a supported media source.
      foreach ($media_sources as $source) {
        if (get_class($handler) == $source['handler_name']) {
          if (isset($field_info['type']) && $field_info['type'] == $source['field_type']) {
            $media_fields[$field] = $field_names[$field];
          }
        }
      }
    }

    // TODO: Detect all field types, populate only compatible fields
    // Add default + supported fields to arrays.
    // Currently only checking support for date fields.
    $text_fields = $text_fields;
    $date_fields = $date_fields;
    $media_fields = $media_fields;

    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('General configuration'),
      '#description' => t('Settings for how the Timeline will behave.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['link_to_entity'] = array(
      '#type' => 'checkbox',
      '#title' => 'Link timeline items to entity',
      '#description' => t('If checked, headlines will be made links to entity.'),
      '#default_value' => isset($this->options['timeline_config']['link_to_entity']) ? $this->options['timeline_config']['link_to_entity'] : '',
    );
    $form['timeline_config']['link_text_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Add a link to entity after bodytext',
      '#description' => t('Append a link to original entity to the end of the bodytext.'),
      '#default_value' => isset($this->options['timeline_config']['link_text_enabled']) ? $this->options['timeline_config']['link_text_enabled'] : '',
    );
    $form['timeline_config']['link_text'] = array(
      '#type' => 'textfield',
      '#title' => 'Link text',
      '#description' => t('Text that will be used in the link to entity'),
      '#default_value' => isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : 'Read more',
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[timeline_config][link_to_entity]"]' => array('value' => 1),
        ),
      ),
    );
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Select the fields to be used for different parts of the timeline.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
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
    $form['timeline_fields']['startDate'] = array(
      '#type' => 'select',
      '#options' => $date_fields,
      '#title' => 'Start Date',
      '#description' => t('Only UNIX timestamp-like date fields are currently supported (node created, updated, etc...)'),
      '#default_value' => isset($this->options['timeline_fields']['startDate']) ? $this->options['timeline_fields']['startDate'] : '',
    );
    $form['timeline_fields']['endDate'] = array(
      '#type' => 'select',
      '#options' => $date_fields,
      '#title' => t('End Date'),
      '#description' => t('Only UNIX timestamp-like date fields are currently supported (node created, updated, etc...)'),
      '#default_value' => isset($this->options['timeline_fields']['endDate']) ? $this->options['timeline_fields']['endDate'] : '',
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $media_fields,
      '#title' => 'Select field for media asset',
      '#description' => t('Only image fields are currently supported'),
      '#default_value' => isset($this->options['timeline_fields']['media']) ? $this->options['timeline_fields']['media'] : '',
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#title' => t('Credits'),
      '#options' => $text_fields,
      '#default_value' => isset($this->options['timeline_fields']['credit']) ? $this->options['timeline_fields']['credit'] : '',
    );
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#title' => t('Captions'),
      '#options' => $text_fields,
      '#default_value' => isset($this->options['timeline_fields']['caption']) ? $this->options['timeline_fields']['caption'] : '',
    );
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $view = $this->view;

    // We want to render some fields, because of field
    // rewriting and other field level processing
    $this->view->style_plugin->render_fields($this->view->result);

    $field_mapping = array(
      'startDate' => 'startDate',
      'endDate' => 'endDate',
      'headline' => 'headline',
      'text' => 'bodytext',
      'media' => 'media',
      'caption' => 'caption',
      'credit' => 'credit',
    );
    $link_text = isset($this->options['timeline_config']['link_text']) ? $this->options['timeline_config']['link_text'] : 'Read more';
    $rows = array();

    // TODO: Figure out how to detect field types and different rendering methods for them.
    $media_field_type = isset($this->options['timeline_fields']['media']) ? $view->field[$this->options['timeline_fields']['media']]->field_info['type'] : NULL;

    // Build a TimelineJS friendly array from the views data
    foreach($this->view->result as $count => $row) {
      // Get the link to entity
      // TODO: Currently restricted to node views, should work with other entities also
      if ($this->options['timeline_config']['link_to_entity'] && $view->base_table == 'node' && isset($row->_field_data[$view->base_field]['entity'])) {
        $row->uri = entity_uri($row->_field_data[$view->base_field]['entity_type'], $row->_field_data[$view->base_field]['entity']);
        $row->link_to_entity = l(t(check_plain($link_text)), $row->uri['path']);
      }

      $data = array();
      $data['asset'] = array();
      // Build the data we need.
      foreach($field_mapping as $target_field => $source_field) {
        $tmp = $this->getDefinedUsage($source_field);

        if ($target_field == 'text') {
          $v_text = $view->field[$tmp['fieldname']]->get_value($row);
          if (is_array($v_text)) {
            $v_text = array_shift($v_text);
          }
          $rows[$count][$target_field] = $v_text['value'];

          $rows[$count][$target_field] = strip_tags($rows[$count][$target_field]);
          if (isset($this->options['timeline_config']['link_text_enabled'])) {
            $rows[$count][$target_field] .= theme('views_timelinejs_link_to_entity', array('uri' => $row->uri['path'], 'link_text' => t($link_text)));
          }
        }

        if ($target_field == 'headline') {
          /**
           * These should always be text fields.
           * Treat them as such until further notice.
           */
          $v_text = $view->field[$tmp['fieldname']]->get_value($row);
          if (is_array($v_text)) {
            $v_text = array_shift($v_text);
          }
          if (!is_string($v_text)) {
            $v_text = $v_text['value'];
          }
          $rows[$count][$target_field] = check_plain($v_text);
        }

        if(in_array($target_field, array('startDate', 'endDate'))) {
          $date = array();
          // Load field data.
          #$value = $view->style_plugin->get_field_value($count, $this->options['timeline_fields'][$source_field]);
          $value = $view->field[$tmp['fieldname']]->get_value($row);
          // If it's a date field, we have an array.
          if (is_array($value)) {
            $value = array_shift($value);
          }

          // Make sure created and changed fields work as date sources.
          if($tmp['fieldname'] == 'created' || $tmp['fieldname'] == 'changed') {
            $tmp['field_type'] = 'date';
          }

          dfb($tmp, 'Field', FirePHP::LOG);
          if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'date_sources')) {
            $date['formatted'] = call_user_func($conversion_callback, $value, 'iso8601', array('field' => $tmp));
            $date['timestamp'] = call_user_func($conversion_callback, $value, 'timestamp', array('field' => $tmp));
          }

          if (isset($date) && $date != "") {
            if (is_array($date['formatted'])) {
              if ($target_field == 'startDate') {
                $rows[$count][$target_field] = check_plain($date['formatted']['value']);
              }
              elseif ($target_field == 'endDate') {
                $rows[$count][$target_field] = check_plain($date['formatted']['value2']);
              }
            }
            else {
              $rows[$count][$target_field] = check_plain($date['formatted']);
            }
          }
        }
        if (in_array($target_field, array('caption', 'credit'))) {
          /**
           * These should always be text fields.
           * Treat them as such until further notice.
           */
          if ($tmp['handler'] != NULL) {
            $v_text = $view->field[$tmp['fieldname']]->get_value($row);
            if (is_array($v_text)) {
              $v_text = array_shift($v_text);
            }
            if (!is_string($v_text)) {
              $v_text = $v_text['value'];
            }
            $rows[$count]['asset'][$target_field] = check_plain($v_text);
          }
        }
        if ($target_field == 'media') {
          $value = $view->field[$tmp['fieldname']]->get_value($row);
          if (is_array($value)) {
            $value = array_shift($value);
          }
          if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'media_sources')) {
            $media['formatted'] = call_user_func($conversion_callback, $value, array('field' => $tmp));
          }
          #dfb($media, 'Media', FirePHP::LOG);
          $rows[$count]['asset'][$target_field] = check_plain($media['formatted']);
        }
      }
    }
    // Let modules alter timeline data before rendering by implementing
    // hook_views_timelinejs_data_alter(&$rows, $view)
    drupal_alter('views_timelinejs_data', $rows, clone $view);

    // Prepare data array that TimelineJS understands
    $data = array(
      'timeline' => array(
        'headline' => 'Title',
        'type' => 'default',
        'date' => $rows,
      ),
    );

    // Skip rendering if view is being edited or previewed
    if(!$view->editing) {
      return theme('views_timelinejs', array('view' => $view, 'options' => $this->options, 'rows' => $data));
    }
    else {
      return '<pre>' . print_r($data, 1) . '</pre>';
      //return t('TimelineJS style does not support preview mode.');
    }
  }

  function getDefinedUsage($type) {
    $view = $this->view;
    $fieldname = '';
    if ($fields = $view->style_options['timeline_fields']) {
      if (isset($fields[$type])) {
        $fieldname = $fields[$type];
      }
      elseif (isset($fields['advanced'][$type])) {
        $fieldname = $fields['advanced'][$type];
      }

      if (isset($fieldname) && $fieldname != '0') {
        $field_information = array(
          'alias' => $view->field[$fieldname]->field_alias,
          'handler' => $view->field[$fieldname]->definition['handler'],
          'fieldname' => $fieldname,
        );
      }
      if (!empty($view->field[$fieldname]->field_info)) {
          $field_information['field_type'] = $view->field[$fieldname]->field_info['type'];
          $field_information['date_format'] = $field_information['field_type'];
          $field_information['tz_handling'] = 'site';
      }

      if (!empty($field_information)) {
        return $field_information;
      }
      else {
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }
}
