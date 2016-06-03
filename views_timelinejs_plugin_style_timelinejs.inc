<?php
/**
 * @file
 * Views Style.
 */

/**
 * Unformatted style plugin.
 */
class views_timelinejs_plugin_style_timelinejs extends views_plugin_style {

  /**
   * Define option defaults.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['timeline_theme'] = array(
      'contains' => array(
        'width' => array(
          'default' => '100',
        ),
        'width_unit' => array(
          'default' => '1',
        ),
        'height' => array(
          'default' => '500',
        ),
        'height_unit' => array(
          'default' => '0',
        ),
      ),
    );
    $options['timeline_fields'] = array(
      'contains' => array(
        'caption' => array(
          'default' => '0',
        ),
        'credit' => array(
          'default' => '0',
        ),
        'media' => array(
          'default' => '0',
        ),
        'tag' => array(
          'default' => '0',
        ),
        'date' => array(
          'default' => '0',
        ),
        'bodytext' => array(
          'default' => '0',
        ),
        'headline' => array(
          'default' => '0',
        ),
        'background' => array(
          'default' => '0',
        ),
      ),
    );
    $options['timeline_config'] = array(
      'contains' => array(
        'hash_bookmark' => array(
          'default' => '0',
        ),
        'start_at_end' => array(
          'default' => '0',
        ),
        'start_at_current' => array(
          'default' => '0',
        ),
        'scale_factor' => array(
          'default' => '2',
        ),
        'language' => array(
          'default' => '',
        ),
        /*'font' => array(
          'default' => '',
        ),*/
      ),
    );
    return $options;
  }

  /**
   * Define options form.
   */
  function options_form(&$form, &$form_state) {
    $initial_labels = array('' => t('- None -'));
    $view_fields_labels = $this->display->handler->get_field_labels();
    $view_fields_labels = array_merge($initial_labels, $view_fields_labels);

    // Timeline general configuration.
    $form['timeline_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('General configuration'),
      '#description' => t('Settings for how the Timeline will behave.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_config']['hash_bookmark'] = array(
      '#type' => 'select',
      '#title' => 'Hash Bookmarks',
      '#description' => t('On each slide, a # will be added to the end of the url in the url bar. These urls are bookmarkable, so you can share or return to the same place in the timeline later.'),
      '#options' => array(
        '0' => t('No'),
        '1' => t('Yes'),
      ),
      '#default_value' => $this->options['timeline_config']['hash_bookmark'],
    );
    $form['timeline_config']['start_at_end'] = array(
      '#type' => 'select',
      '#title' => 'Start at the end',
      '#description' => t('The most recent event will be shown first.'),
      '#options' => array(
        '0' => t('No'),
        '1' => t('Yes'),
      ),
      '#default_value' => $this->options['timeline_config']['start_at_end'],
    );
    $form['timeline_config']['start_at_current'] = array(
      '#type' => 'select',
      '#title' => 'Start at Current',
      '#description' => t('The slide closest to current time.'),
      '#options' => array(
        '0' => t('No'),
        '1' => t('Yes'),
      ),
      '#default_value' => $this->options['timeline_config']['start_at_current'],
    );
    $form['timeline_config']['scale_factor'] = array(
      '#type' => 'select',
      '#title' => 'Scale factor',
      '#description' => t('How many screen widths wide the timeline should be at first presentation.'),
      '#options' => array(
        '1' => t('1'),
        '2' => t('2'),
        '3' => t('3'),
        '4' => t('4'),
        '5' => t('5'),
        '6' => t('6'),
        '7' => t('7'),
        '8' => t('8'),
        '9' => t('9'),
      ),
      '#default_value' => $this->options['timeline_config']['scale_factor'],
    );
    $form['timeline_config']['language'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#title' => 'Language',
      '#description' => t('The language <a href="https://github.com/NUKnightLab/TimelineJS#language">code</a>. Leave blank for the site language.'),
      '#default_value' => $this->options['timeline_config']['language'],
    );
    /*$form['timeline_config']['font'] = array(
      '#type' => 'select',
      '#title' => 'Font',
      '#description' => t('This setting will only have an effect if the selected font is available to the site (ie @font-face).'),
      '#options' => array(
        '' => t('Default'),
        'AbrilFatface-Average' => 'AbrilFatface-Average',
        'Arvo-PTSans' => 'Arvo-PTSans',
        'Bevan-PotanoSans' => 'Bevan-PotanoSans',
        'BreeSerif-OpenSans' => 'BreeSerif-OpenSans',
        'DroidSerif-DroidSans' => 'DroidSerif-DroidSans',
        'Georgia-Helvetica' => 'Georgia-Helvetica',
        'Lekton-Molengo' => 'Lekton-Molengo',
        'Merriweather-NewsCycle' => 'Merriweather-NewsCycle',
        'NewsCycle-Merriweather' => 'NewsCycle-Merriweather',
        'NixieOne-Ledger' => 'NixieOne-Ledger',
        'Pacifico-Arimo' => 'Pacifico-Arimo',
        'PlayfairDisplay-Muli' => 'PlayfairDisplay-Muli',
        'PoiretOne-Molengo' => 'PoiretOne-Molengo',
        'PTSerif-PTSans' => 'PTSerif-PTSans',
        'PT' => 'PT',
        'Rancho-Gudea' => 'Rancho-Gudea',
        'SansitaOne-Kameron' => 'SansitaOne-Kameron',
      ),
      '#default_value' => $this->options['timeline_config']['font'],
    );*/

    // Field mapping.
    $form['timeline_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field mappings'),
      '#description' => t('Fields used to construct the timeline events.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_fields']['headline'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Headline'),
      '#required' => TRUE,
      '#description' => t('Plain text; a high level summary.'),
      '#default_value' => $this->options['timeline_fields']['headline'],
    );
    $form['timeline_fields']['bodytext'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Body text'),
      '#description' => t('Plain text; a paragraph or two of optional details.'),
      '#default_value' => $this->options['timeline_fields']['bodytext'],
    );
    $form['timeline_fields']['date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Start and End date'),
      '#required' => TRUE,
      '#description' => t('Required start and optional end of an event; can be a date field or timestamp.'),
      '#default_value' => $this->options['timeline_fields']['date'],
    );
    $form['timeline_fields']['background'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Background image'),
      '#description' => t('Drupal core image fields and link fields are supported; must contain a raw URL to an image.'),
      '#default_value' => $this->options['timeline_fields']['background'],
    );
    $form['timeline_fields']['media'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Media URL'),
      '#description' => t('Drupal core image fields and link fields are supported; must contain a raw URL to an image or video.'),
      '#default_value' => $this->options['timeline_fields']['media'],
    );
    $form['timeline_fields']['credit'] = array(
      '#type' => 'select',
      '#title' => t('Media Credit'),
      '#description' => t('Byline naming the author or attributing the source.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['credit'],
    );
    $form['timeline_fields']['caption'] = array(
      '#type' => 'select',
      '#title' => t('Media Caption'),
      '#description' => t('Brief explanation of the media content.'),
      '#options' => $view_fields_labels,
      '#default_value' => $this->options['timeline_fields']['caption'],
    );
    $form['timeline_fields']['tag'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Tag'),
      '#description' => t('Content tagging; maximum of 6 tags.'),
      '#default_value' => $this->options['timeline_fields']['tag'],
    );

    // Timeline display configuration.
    $units = array(0 => 'px', 1 => '%');
    $form['timeline_theme'] = array(
      '#type' => 'fieldset',
      '#title' => t('Display configuration'),
      '#description' => t('Settings for how the Timeline will look.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['timeline_theme']['width'] = array(
      '#type' => 'textfield',
      '#title' => 'Width of the timeline',
      '#description' => t('The width of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['width'],
    );
    $form['timeline_theme']['width_unit'] = array(
      '#type' => 'radios',
      '#title' => t('Units for the width'),
      '#description' => t('Choose which units will be used to define the width of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['width_unit'],
      '#options' => $units,
    );
    $form['timeline_theme']['height'] = array(
      '#type' => 'textfield',
      '#title' => 'Height of the timeline',
      '#description' => t('The height of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['height'],
    );
    $form['timeline_theme']['height_unit'] = array(
      '#type' => 'radios',
      '#title' => t('Units for the height'),
      '#description' => t('Choose which units will be used to define the height of the timeline.'),
      '#default_value' => $this->options['timeline_theme']['height_unit'],
      '#options' => $units,
    );
  }

  /**
   * {@inheritdoc}
   */
  function validate() {
    $errors = parent::validate();

    // Validate that fields have been assigned to the required options.
    foreach (array('date', 'headline') as $required_option) {
      if (empty($this->options['timeline_fields'][$required_option])) {
        $errors[] = t('The TimelineJS plugin requires specifying which views fields to use for the event slides.');
        break;
      }
    }
    return $errors;
  }

  /**
   * Render the display.
   */
  function render() {
    $field_mapping = array(
      'start_date' => 'date',
      'end_date' => 'date',
      'headline' => 'headline',
      'text' => 'bodytext',
      'background' => 'background',
      'media' => 'media',
      'caption' => 'caption',
      'credit' => 'credit',
      'group' => 'tag',
    );
    $slides = array();

    // Render fields to trigger rewriting and other field processing.
    $this->view->style_plugin->render_fields($this->view->result);

    if (!empty($this->view->style_options['timeline_config']['start_at_current'])) {
      // Gives you a timestamp of the date
      $date_check = strtotime('now');
      // Holds the difference of the closest date
      $difference = NULL;
      // Holds the index in the array
      $start_at_current = NULL;
    }

    // Build a TimelineJS friendly array from the views data.
    $this->view->row_index = 0;
    foreach ($this->view->result as $count => $result) {

      $this->view->row_index = $count;
      $slide['text'] = array();
      $slide['media'] = array();

      // Build the data we need.
      foreach ($field_mapping as $target_field => $source_field) {
        $tmp = $this->getDefinedUsage($source_field);

        // Don't render fields that haven't been mapped.
        if (!isset($this->view->field[$tmp['fieldname']])) {
          continue;
        }

        // Headline - can use any view field, uses views rendering.
        if ($target_field == 'headline') {
          $headline_field = $this->view->style_options['timeline_fields']['headline'];
          $slide['text'][$target_field] = $this->rendered_fields[$count][$headline_field];
        }

        // Body - can use any view field, uses views rendering.
        if ($target_field == 'text') {
          $body_field = $this->view->style_options['timeline_fields']['bodytext'];
          $slide['text'][$target_field] = $this->rendered_fields[$count][$body_field];
        }

        // Tag.
        if ($target_field == 'group') {
          $value = '';
          // Check if if a tag exists.
          if (isset($this->view->field[$tmp['fieldname']])) {
            $value = $this->view->field[$tmp['fieldname']]->get_value($result);
            if (is_array($value)) {
              $value = array_shift($value);
            }

            if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'tag_sources')) {
              $value = call_user_func($conversion_callback, $value, array(
                'field' => $tmp,
              ));
            }
          }
          $slide[$target_field] = check_plain($value);
        }

        // Start and End date.
        if (in_array($target_field, array('start_date', 'end_date'))) {
          $date = array();
          // Load field data.
          $value = $this->view->field[$tmp['fieldname']]->get_value($result);
          // If it's a date field, we have an array.
          if (is_array($value)) {
            $value = array_shift($value);
          }


          // Make sure created and changed fields work as date sources.
          if ($tmp['fieldname'] == 'created' || $tmp['fieldname'] == 'changed') {
            $tmp['field_type'] = 'date';
          }

          if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'date_sources')) {
            $date['formatted'] = call_user_func($conversion_callback, $value, 'csv', array('field' => $tmp));
            $date['timestamp'] = call_user_func($conversion_callback, $value, 'timestamp', array('field' => $tmp));
            if (!empty($date['timestamp']['value'])) {
              $date['start']['fields'] = localtime($date['timestamp']['value'], true);
            }
            if (!empty($date['timestamp']['value2'])) {
              $date['end']['fields'] = localtime($date['timestamp']['value2'], true);
            }
          }

          if (isset($date) && $date) {
            if (!empty($date['start']['fields']) && $target_field == 'start_date') {
              $slide[$target_field] = array();
              $slide[$target_field]['year'] = $date['start']['fields']['tm_year'] + 1900;
              $slide[$target_field]['month'] = $date['start']['fields']['tm_mon'] + 1;
              $slide[$target_field]['day'] = $date['start']['fields']['tm_mday'];
              $slide[$target_field]['hour'] = $date['start']['fields']['tm_hour'];
              $slide[$target_field]['minute'] = $date['start']['fields']['tm_min'];
              $slide[$target_field]['second'] = $date['start']['fields']['tm_sec'];
            }
            elseif (!empty($date['end']['fields']) && $target_field == 'end_date') {
              $slide[$target_field] = array();
              $slide[$target_field]['year'] = $date['end']['fields']['tm_year'] + 1900;
              $slide[$target_field]['month'] = $date['end']['fields']['tm_mon'] + 1;
              $slide[$target_field]['day'] = $date['end']['fields']['tm_mday'];
              $slide[$target_field]['hour'] = $date['end']['fields']['tm_hour'];
              $slide[$target_field]['minute'] = $date['end']['fields']['tm_min'];
              $slide[$target_field]['second'] = $date['end']['fields']['tm_sec'];
            }
            else {
              unset($slide[$target_field]);
            }

            if (is_array($date['formatted'])) {
              if ($target_field == 'start_date') {

                if ($date['formatted']['value'] != "FALSE") {
                  if (!empty($this->view->style_options['timeline_config']['start_at_current'])) {
                    // abs to get the absolute difference
                    $diff = abs($date['timestamp']['value'] - $date_check);

                    // If the difference is smaller than the absolute difference of the last date we need to update our values here
                    if ($difference == NULL || $diff < $difference) {
                      $difference = $diff;
                      $start_at_current = $count;
                    }
                  }

                  //$slide[$target_field]['display_date'] = check_plain($date['formatted']['value']);
                  $rendered_date = strip_tags($this->rendered_fields[$count][$tmp['fieldname']]);
                  $slide[$target_field]['display_date'] = preg_replace('/(\sto.*)$/', '', $rendered_date);
                }
                else {
                  watchdog('views_timelinejs', "Could not format date for field %field in node @nid. This event will not appear in the timeline.", array('@nid' => $result->nid, '%field' => $tmp['fieldname']), WATCHDOG_WARNING);
                  unset($slide[$target_field]);
                }
              }
              elseif (($target_field == 'end_date') && isset($date['formatted']['value2'])) {
                //$slide[$target_field]['display_date'] = check_plain($date['formatted']['value2']);
                $rendered_date = strip_tags($this->rendered_fields[$count][$tmp['fieldname']]);
                $slide[$target_field]['display_date'] = preg_replace('/^(.+?to\s*)/', '', $rendered_date);

                if ($date['formatted']['value2'] == "FALSE") {
                  watchdog('views_timelinejs', "Could not format date for field %field in node @nid.", array('@nid' => $result->nid, '%field' => $tmp['fieldname']), WATCHDOG_WARNING);
                }
              }
            }
            else {
              $slide[$target_field]['display_date'] = strip_tags($this->rendered_fields[$count][$tmp['fieldname']]);
            }
          }
        }

        // Background URL.
        if ($target_field == 'background' && isset($result->_field_data[$this->view->field[$tmp['fieldname']]->field_alias])) {
          $value = $this->view->field[$tmp['fieldname']]->get_value($result);
          if (empty($value) && !empty($this->view->field[$tmp['fieldname']]->options['empty'])) {
            $token = $this->view->field[$tmp['fieldname']]->options['empty'];
            $token = substr($token, 0, strpos($token, ']'));
            $token = str_replace(array('[', ']'), '', $token);

            // We've got to replace the $tmp information for proper handling.
            $tmp['fieldname'] = $token;
            $tmp['field_type'] = $this->view->field[$token]->field_info['type'];
            $tmp['handler'] = $this->view->field[$token]->definition['handler'];
            $tmp['alias'] = $this->view->field[$token]->field_alias;

            $value = $this->view->field[$token]->get_value($result);
          }

          if (is_array($value)) {
            $value = array_shift($value);
            // Allow for imagefield image style selection.
            if ($this->view->field[$tmp['fieldname']]->options['settings']['image_style'] && !empty($value['uri'])) {
              $value['uri'] = image_style_url($this->view->field[$tmp['fieldname']]->options['settings']['image_style'], $value['uri']);
            }
          }
          if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'media_sources')) {
            $media['formatted'] = call_user_func($conversion_callback, $value, array('field' => $tmp));
          }

          if ($media['formatted']) {
            $slide[$target_field]['url'] = check_plain($media['formatted']);
          }
        }


        // Media URL.
        if ($target_field == 'media' && isset($result->_field_data[$this->view->field[$tmp['fieldname']]->field_alias])) {
          $value = $this->view->field[$tmp['fieldname']]->get_value($result);
          if (empty($value) && !empty($this->view->field[$tmp['fieldname']]->options['empty'])) {
            $token = $this->view->field[$tmp['fieldname']]->options['empty'];
            $token = substr($token, 0, strpos($token, ']'));
            $token = str_replace(array('[', ']'), '', $token);

            // We've got to replace the $tmp information for proper handling.
            $tmp['fieldname'] = $token;
            $tmp['field_type'] = $this->view->field[$token]->field_info['type'];
            $tmp['handler'] = $this->view->field[$token]->definition['handler'];
            $tmp['alias'] = $this->view->field[$token]->field_alias;

            $value = $this->view->field[$token]->get_value($result);
          }

          if (is_array($value)) {
            $value = array_shift($value);
            // Allow for imagefield image style selection.
            if (isset($this->view->field[$tmp['fieldname']]->options['settings']['image_style']) && !empty($value['uri'])) {
              $value['uri'] = image_style_url($this->view->field[$tmp['fieldname']]->options['settings']['image_style'], $value['uri']);
            }
          }
          if ($conversion_callback = views_timelinejs_get_callback($tmp['handler'], $tmp['field_type'], 'media_sources')) {
            $media['formatted'] = call_user_func($conversion_callback, $value, array('field' => $tmp));
          }

          if ($media['formatted']) {
            $slide[$target_field]['url'] = check_plain($media['formatted']);
            $slide[$target_field]['thumbnail'] = check_plain($media['formatted']);
          }
        }

        // Media Caption, Media Credit - both plain text.
        if (in_array($target_field, array('caption', 'credit'))) {
          if ($tmp['handler'] != NULL) {
            $v_text = $this->view->field[$tmp['fieldname']]->get_value($result);
            if (is_array($v_text)) {
              $v_text = array_shift($v_text);
            }
            if (!is_string($v_text)) {
              $v_text = $v_text['value'];
            }
            if ($v_text) {
              $slide['media'][$target_field] = check_plain($v_text);
            }
          }
        }
      }
      $slides[] = $slide;
    }
    unset($this->view->row_index);

    // Allow other modules to alter timeline slides before rendering by
    // implementing hook_views_timelinejs_rows_alter().
    drupal_alter('views_timelinejs_rows', $slides, clone $this->view);

    // Ensure all slides still have a start date after the drupal alter.
    foreach ($slides as $i => $slide) {
      if (empty($slide['start_date'])) {
        unset($slides[$i]);
      }
    }
    // Reset the indices.
    $slides = array_values($slides);

    // Prepare data array that TimelineJS understands.
    $data = array(
      'scale' => 'human',
      'events' => $slides,
    );
    if (!empty($this->view->style_options['timeline_config']['start_at_current'])) {
      $data['timeline']['start_at_current'] = $start_at_current;
    }

    // Allow other modules to alter timeline data before rendering by
    // implementing hook_views_timelinejs_data_alter().
    drupal_alter('views_timelinejs_data', $data, clone $this->view);

    // Skip rendering if view is being edited or previewed.
    if (!$this->view->editing) {
      return theme('views_timelinejs', array(
        'view' => $this->view,
        'options' => $this->options,
        'rows' => $data,
      ));
    }
    else {
      return '<pre>' . print_r($data, 1) . '</pre>';
    }
  }

  /**
   * Helper function to determine alias, handler, and fieldname of a given type.
   *
   * @param string $type
   *   The type to be parsed.
   *
   * @return array|boolean
   *   An array containing the keys/values for: alias, handler, fieldname,
   *   field_type, date_format, and tz_handling.
   */
  protected function getDefinedUsage($type) {
    // If it's not mapped at all, don't do anything.
    if (!isset($this->view->style_options['timeline_fields'])) {
      return FALSE;
    }

    if ($fields = $this->view->style_options['timeline_fields']) {
      $fieldname = '';
      if (isset($fields[$type])) {
        $fieldname = $fields[$type];
      }
      elseif (isset($fields['advanced'][$type])) {
        $fieldname = $fields['advanced'][$type];
      }
      if (!empty($fieldname)) {
        $field_information = array(
          'alias' => $this->view->field[$fieldname]->field_alias,
          'handler' => $this->view->field[$fieldname]->definition['handler'],
          'fieldname' => $fieldname,
        );
      }

      if (!empty($this->view->field[$fieldname]->field_info)) {
        $field_information['field_type'] = $this->view->field[$fieldname]->field_info['type'];
        $field_information['date_format'] = $field_information['field_type'];

        // If we're dealing with a date-field, get tz_handling and granularity as well.
        if (isset($this->view->field[$fieldname]->field_info['settings']['tz_handling'])) {
          $field_information['tz_handling'] = $this->view->field[$fieldname]->field_info['settings']['tz_handling'];
        }
        if (isset($this->view->field[$fieldname]->field_info['settings']['granularity'])) {
          $field_information['granularity'] = $this->view->field[$fieldname]->field_info['settings']['granularity'];
        }
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
