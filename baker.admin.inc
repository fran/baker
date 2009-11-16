<?php
function baker_admin_form()
{ $form = array();
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => True,
    '#description' => t('Define the title of the url defined in the previous input.')
  );
  
  $form['source'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#required' => True,
    '#description' => t('Define the Url to assign the title that will be defined.')
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
  //$breadcrumb = (object)$form_state['values'];
  //aquí se guardaría la configuración definida
  $form_state['redirect'] = 'admin/build/baker';
}
