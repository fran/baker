<?php
function baker_admin_form()
{ $form = array();

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#required' => True,
    '#description' => t('Define the Url to assign the title that will be defined.')
  );
  
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => True,
    '#description' => t('Define the title of the url defined in the previous input.')
  );
  
  
  $form['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Target'),
    '#required' => False,
    '#description' => t('Define the Url to redirect when click the breadcrumb')
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  return $form;
}

/**
 * Generate the HTML code for the administation page, the urls/titles table and the acctions to manage them.
 *
 * @return The view of the page
 * @author fran
 **/
function baker_administration_page()
{
  $output = _baker_popups_links();
  
  return $output;
}

function _baker_popups_links(){
  popups_add_popups();
  $output =  l("Add new title", 'admin/build/baker/add',
               array( 'attributes' => array('class' => 'popups-form')));
  return $output;

}
/*
function baker_admin_form_validate($form, &$form_state) {
  //validaciones de la configuración del formulario
}
*/
function baker_admin_form_submit($form, &$form_state) {
  $customItem = (object)$form_state['values'];
  _baker_save_custom_bread($customItem);
  //aquí se guardaría la configuración definida
  
  $form_state['redirect'] = 'admin/build/baker';
}

/**
 * Save the user input from administration panel
 *
 * @return void
 * @author fran
 **/
function _baker_save_custom_bread($customItem = null) 
{ 
  if (isset($customItem->cid)) {
    drupal_write_record('baker', $customItem, 'bid');
  }
  else {
    drupal_write_record('baker', $customItem);
  }
}