<?php

/**
 * @file
 * Include file for services_basic_auth module.
 */

/**
 * Authenticates a call using HTTP basic authentication to verify the request.
 *
 * @param array $settings
 *   The settings for the authentication module.
 * @param array $method
 *   The method that's being called.
 * @param array $args
 *   The arguments that are being used to call the method.
 *
 * @return void|string
 *   Returns nothing, or a error message if authentication fails.
 */
function _services_basic_auth_authenticate_call($settings, $method, $args) {
  // PHP FastCGI doesn't support HTTP Basic Authentication out of the box so we
  // need this workaround. Requires a patch to .htaccess.
  // @see http://drupal.org/node/1864628.
  if (isset($_SERVER['HTTP_AUTHORIZATION']) AND !empty($_SERVER['HTTP_AUTHORIZATION'])) {
    list($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']) = explode(':', base64_decode(substr($_SERVER['HTTP_AUTHORIZATION'], 6)), 2);
  }

  if (user_is_anonymous() && isset($_SERVER['PHP_AUTH_USER']) && isset($_SERVER['PHP_AUTH_PW'])) {
    if($uid = user_authenticate($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW'])) {
      global $user;
      $user = user_load($uid);

      //No session is opened so Drupal may cache the results if caching is enabled
      //Manually disable caching for this request
      $GLOBALS['conf']['cache'] = FALSE;
    }
  }
}
