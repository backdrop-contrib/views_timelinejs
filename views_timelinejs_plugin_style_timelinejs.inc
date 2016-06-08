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
   * The row index of the slide at which the timeline should first be rendered.
   */
  protected $start_slide_index;

  /**
   * Define option defaults.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['timeline_theme'] = array(
      'contains' => array(
        'width' => array('default' => '100'),
        'width_unit' => array('default' => '1'),
        'height' => array('default' => '500'),
        'height_unit' => array('default' => '0'),
      ),
    );
    $options['timeline_fields'] = array(
      'contains' => array(
        'caption' => array('default' => ''),
        'credit' => array('default' => ''),
        'media' => array('default' => ''),
        'group' => array('default' => ''),
        'date' => array('default' => ''),
        'text' => array('default' => ''),
        'headline' => array('default' => ''),
        'background' => array('default' => ''),
      ),
    );
    $options['timeline_config'] = array(
      'contains' => array(
        'hash_bookmark' => array('default' => '0'),
        'start_at_end' => array('default' => '0'),
        'start_at_current' => array('default' => '0'),
        'scale_factor' => array('default' => '2'),
        'language' => array('default' => ''),
        /*'font' => array('default' => ''),*/
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
    $form['timeline_fields']['text'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Body text'),
      '#description' => t('Plain text; a paragraph or two of optional details.'),
      '#default_value' => $this->options['timeline_fields']['text'],
    );
    $form['timeline_fields']['start_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Start date'),
      '#required' => TRUE,
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['start_date'],
    );
    $form['timeline_fields']['end_date'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('End date'),
      '#description' => t('The selected field should contain a string representing a date conforming to a <a href="@php-manual">PHP supported date and time format</a>.', array('@php-manual' => 'http://php.net/manual/en/datetime.formats.php')),
      '#default_value' => $this->options['timeline_fields']['end_date'],
    );
    $form['timeline_fields']['background'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Background image'),
      '#description' => t('The selected field should contain a raw URL to an image.  Special handling is included for Image fields because they have no raw URL formatter.'),
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
    $form['timeline_fields']['group'] = array(
      '#type' => 'select',
      '#options' => $view_fields_labels,
      '#title' => t('Group'),
      '#description' => t('Any text. If present, TimelineJS will organize events with the same value for group to be in the same row or adjacent rows, separate from events in other groups. The common value for the group will be shown as a label at the left edge of the navigation.'),
      '#default_value' => $this->options['timeline_fields']['group'],
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
    foreach (array('start_date', 'headline') as $required_option) {
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
    $slides = array();

    // Render fields to trigger rewriting and other field processing.
    $this->view->style_plugin->render_fields($this->view->result);

    // Render slide arrays from the views data.
    foreach ($this->view->result as $row_index => $row) {
      $this->view->row_index = $row_index;
      $slides[] = $this->render_slide($row);
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
    if (!empty($this->options['timeline_config']['start_at_current'])) {
      $data['timeline']['start_at_current'] = $this->start_slide_index;
    }

    // Allow other modules to alter timeline data before rendering by
    // implementing hook_views_timelinejs_data_alter().
    drupal_alter('views_timelinejs_data', $data, clone $this->view);

    // Skip theming if the view is being edited or previewed.
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
   * Renders a TimelineJS slide from a views data row.
   *
   * @param type $row
   *   A views result row.
   *
   * @return array
   *   A array representing an individual TimelineJS slide.
   */
  protected function render_slide($row) {
    // Store the row index so the code is a little easier to read.
    $row_index = $this->view->row_index;

    $slide = array();
    $slide['text'] = array();
    $slide['media'] = array();

    if ($this->options['timeline_fields']['headline']) {
      $slide['text']['headline'] = $this->get_field($row_index, $this->options['timeline_fields']['headline']);
    }

    if ($this->options['timeline_fields']['text']) {
      $slide['text']['text'] = $this->get_field($row_index, $this->options['timeline_fields']['text']);
    }

    if ($this->options['timeline_fields']['group']) {
      $slide['group'] = $this->get_field($row_index, $this->options['timeline_fields']['group']);
    }

    if ($this->options['timeline_fields']['start_date']) {
      $start_date_value = $this->get_field($row_index, $this->options['timeline_fields']['start_date']);
      if (!empty($start_date_value)) {
        // Format the date for TimelineJS3.
        $start_date = new TimelineDate($start_date_value);
        $slide['start_date'] = $start_date->getTimelineDateArray();

        // Check to see if this slide should be the start slide.
        $this->check_start_slide($start_date);
      }
    }

    if ($this->options['timeline_fields']['end_date'] && !empty($start_date_value)) {
      $end_date_value = $this->get_field($row_index, $this->options['timeline_fields']['end_date']);

      // Don't render end dates that are the same as the start date.  TimelineJS
      // won't display them anyway, but skipping them can make the rendered data
      // array smaller.
      if (!empty($end_date_value) && $start_date_value !== $end_date_value) {
        // Format the date for TimelineJS3.
        $end_date = new TimelineDate($end_date_value);
        $slide['end_date'] = $end_date->getTimelineDateArray();
      }
    }

    if ($this->options['timeline_fields']['background']) {
      $background_url_value = $this->get_field($row_index, $this->options['timeline_fields']['background']);

      // Special handling because core Image fields have no raw URL formatter.
      // Check to see if we don't have a raw URL.
      if (!filter_var($background_url_value, FILTER_VALIDATE_URL)) {
        // Attempt to extract a URL from the string.
        $background_url_value = $this->extract_url($background_url_value);
      }

      if (!empty($background_url_value)) {
        $slide['background']['url'] = $background_url_value;
      }
    }

    $field_mapping = array(
      'media' => 'media',
      'caption' => 'caption',
      'credit' => 'credit',
    );

    // Build the data we need.
    foreach ($field_mapping as $target_field => $source_field) {
      $tmp = $this->getDefinedUsage($source_field);

      // Don't render fields that haven't been mapped.
      if (!isset($this->view->field[$tmp['fieldname']])) {
        continue;
      }

      // Media URL.
      if ($target_field == 'media' && isset($row->_field_data[$this->view->field[$tmp['fieldname']]->field_alias])) {
        $value = $this->view->field[$tmp['fieldname']]->get_value($row);
        if (empty($value) && !empty($this->view->field[$tmp['fieldname']]->options['empty'])) {
          $token = $this->view->field[$tmp['fieldname']]->options['empty'];
          $token = substr($token, 0, strpos($token, ']'));
          $token = str_replace(array('[', ']'), '', $token);

          // We've got to replace the $tmp information for proper handling.
          $tmp['fieldname'] = $token;
          $tmp['field_type'] = $this->view->field[$token]->field_info['type'];
          $tmp['handler'] = $this->view->field[$token]->definition['handler'];
          $tmp['alias'] = $this->view->field[$token]->field_alias;

          $value = $this->view->field[$token]->get_value($row);
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
          $v_text = $this->view->field[$tmp['fieldname']]->get_value($row);
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

    return $slide;
  }

  /**
   * Checks a slide date to see if it should be displayed first in the timeline.
   *
   * @param DateTime $date
   *   A date from a TimelineJS slide.
   */
  protected function check_start_slide(DateTime $date) {
    static $smallest_difference;
    if (!isset($smallest_difference)) {
      $smallest_difference = NULL;
    }

    $timestamp = $date->getTimestamp();
    // Return if the date was prior to the UNIX Epoch.
    if ($timestamp === FALSE) {
      return;
    }

    // Calculate the absolute difference between the current time and the date.
    $difference = abs(time() - $timestamp);

    // Update the start slide index if this date is closer to the current time.
    if ($smallest_difference == NULL || $difference < $smallest_difference) {
      $smallest_difference = $difference;
      $this->start_slide_index = $this->view->row_index;
    }
  }

  /**
   * Searches a string for HTML attributes that contain URLs and returns them.
   *
   * This will search a string which is presumed to contain HTML for anchor or
   * image tags.  It will return the href or src attribute of the first one it
   * finds.
   *
   * This is basically special handling for core Image fields.  There is no
   * built-in field formatter for outputting a raw URL from an image.  This
   * method allows image fields to "just work" as sources for TimelineJS media
   * and background image URLs.  Anchor tag handling was added for people who
   * forget to output link fields as plain text URLs.
   *
   * @param string $html
   *   A string that contains HTML.
   *
   * @return string
   *   A URL if one was found in the input string, empty if not.
   */
  protected function extract_url($html) {
    if (!empty($html)) {
      $document = new DOMDocument();
      $document->loadHTML($html);

      // Check for anchor tags.
      $anchor_tags = $document->getElementsByTagName('a');
      if ($anchor_tags->length) {
        return $anchor_tags->item(0)->getAttribute('href');
      }

      // Check for image tags.
      $image_tags = $document->getElementsByTagName('img');
      if ($image_tags->length) {
        return $image_tags->item(0)->getAttribute('src');
      }
    }
    return '';
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
