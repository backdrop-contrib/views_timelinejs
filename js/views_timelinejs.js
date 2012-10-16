var embed_path;
(function ($) {

  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      embed_path = Drupal.settings.timelineJS['embed_path'];
      createStoryJS(Drupal.settings.timelineJS);
    }
  }

})(jQuery);

