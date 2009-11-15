<?php
function baker_admin_form()
{
  $form['titles'] = array(
    '#type' => 'textarea',
    '#title' => t('Titles'),
    '#required' => FALSE,
    '#description' => t('Listado de los títulos de una url. Para intruducir un título a una url blog/[yyyy] hay que poner una 
                         línea con el par url | título_de_la_url, por ejemplo blog/[yyyy] | por años '),
    '#default_value' => NULL
  );
  
  return $form;
}

function baker_admin_form_validate($form, &$form_state) {
  //validaciones de la configuración del formulario
}

function baker_admin_form_submit($form, &$form_state) {
  $breadcrumb = (object)$form_state['values'];
  //aquí se guardaría la configuración definida
  $form_state['redirect'] = 'admin/build/baker';
}