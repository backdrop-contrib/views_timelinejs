(function ($) {

  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      createStoryJS(Drupal.settings.timelineJS);
    }
  }

})(jQuery);

