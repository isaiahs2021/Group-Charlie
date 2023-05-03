static void       gimp_symmetry_real_get_transform  (GimpSymmetry *sym, gint          gimp_stroke_line, gdouble      *angle, gboolean     *reflect);
                                                     

gimp_symmetry_get_size (GimpSymmetry *sym)
{
  	g_return_val_if_fail (GIMP_IS_SYMMETRY (sym), 0);

  	return g_list_length (sym->strokes);

// returns the total number of strokes
}


gimp_symmetry_get_cords(GimpSymmetry * sym, gint gimp_stroke_line)
{
	g_return_val_if_fail(GIMP_IS_SYMMETRY (sym), NULL);
return g_list_nth_data (sym->strokes, gimp_stroke_line);

//returns the coordinates of the line stroke number

}

gimp_symmetry_get_transform(GimpSymmetry*sym, gint gimp_stroke_line)
{
	g_return_if_fail (GIMP_IS_SYMMETRY (sym));
  	g_return_if_fail (angle != NULL);
  	g_return_if_fail (reflect != NULL);

  	*angle   = 0.0;
  	*reflect = FALSE;

  	GIMP_SYMMETRY_GET_CLASS (sym)->get_transform (sym, gimp_stroke_line);

//the transformation to apply to the paint content for stroke

}
						
gimp_symmetry_get_operation (GimpSymmetry *sym,
                             gint          gimp_stroke_line)
{
//Returns: the transformation operation to apply to the paint content for stroke number @stroke, or NULL for the identity transformation.



gimp_symmetry_get_matrix(GimpSymmetry *sym, gint gimp_stroke_line)
{


  	gdouble  angle;
  	gboolean reflect;

  	g_return_if_fail (GIMP_IS_SYMMETRY (sym));
  	g_return_if_fail (matrix != NULL);

  	gimp_symmetry_get_transform (sym, gimp_stroke_line, &angle, &reflect);

  	gimp_matrix3_identity (matrix);
  	gimp_matrix3_rotate (matrix, -gimp_deg_to_rad (angle));
  	if (reflect)
   	 gimp_matrix3_scale (matrix, -1.0, 1.0);

//apply the transformation matrix to the line content for the stroke
}

__________
//gimpsymmetry-mirror.c
static void
gimp_mirror_update_strokes (GimpSymmetry *sym,
                            GimpDrawable *drawable,
                            GimpCoords   *origin)
{
  GimpMirror *mirror  = GIMP_MIRROR (sym);
  GList      *strokes = NULL;
  GimpCoords *coords;
  gdouble     mirror_position_x, mirror_position_y;
  gint        offset_x,          offset_y;

  gimp_item_get_offset (GIMP_ITEM (drawable), &offset_x, &offset_y);

  mirror_position_x = mirror->mirror_position_x - offset_x;
  mirror_position_y = mirror->mirror_position_y - offset_y;

  g_list_free_full (sym->strokes, g_free);
  strokes = g_list_prepend (strokes,
                            g_memdup2 (origin, sizeof (GimpCoords)));

  if (mirror->horizontal_mirror)
    {
      coords = g_memdup2 (origin, sizeof (GimpCoords));
      coords->y = 2.0 * mirror_position_y - origin->y;
      strokes = g_list_prepend (strokes, coords);
    }

  if (mirror->vertical_mirror)
    {
      coords = g_memdup2 (origin, sizeof (GimpCoords));
      coords->x = 2.0 * mirror_position_x - origin->x;
      strokes = g_list_prepend (strokes, coords);
    }

  if (mirror->point_symmetry)
    {
      coords = g_memdup2 (origin, sizeof (GimpCoords));
      coords->x = 2.0 * mirror_position_x - origin->x;
      coords->y = 2.0 * mirror_position_y - origin->y;
      strokes = g_list_prepend (strokes, coords);
    }

  sym->strokes = g_list_reverse (strokes);

  g_signal_emit_by_name (sym, "strokes-updated", sym->image);
}


