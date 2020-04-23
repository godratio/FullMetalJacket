
//NOTE(Ray):These are convienent methods for those using yoyoyo data formats for abstractions
void fmj_3dtrans_matrix_set(FMJ3DTrans* ot)
{
	ot->m = f4x4_create_from_trs(ot->p,ot->r,ot->s);
}

f3 fmj_3dtrans_world_to_local_pos(FMJ3DTrans* ot,f3 a)
{
    fmj_3dtrans_matrix_set(ot);
	return f3_world_local_p(ot->m,a);
}

f3 fmj_3dtrans_local_to_world_pos(FMJ3DTrans* ot,f3 a)
{
    fmj_3dtrans_matrix_set(ot);
	return f3_local_world_p(ot->m,a);
}

void fmj_3dtrans_update(FMJ3DTrans* ot)
{
    fmj_3dtrans_matrix_set(ot);
	ot->up = quaternion_up(ot->r); 
	ot->right = quaternion_right(ot->r);
	ot->forward = quaternion_forward(ot->r);
}

void fmj_3dtrans_init(FMJ3DTrans* ot)
{
    ot->r = quaternion_identity();
    ot->s = f3_create(1,1,1);
    ot->p = f3_create(0,0,0);
    ot->local_r = quaternion_identity();
    ot->local_s = f3_create(1,1,1);
    ot->local_p = f3_create(0,0,0);
    fmj_3dtrans_update(ot);
}

f4x4 fmj_3dtrans_set_cam_view(FMJ3DTrans* ot)
{
    fmj_3dtrans_update(ot);
    return set_camera_view(ot->p,ot->forward,ot->up);
}

f3 fmj_3dtrans_transform_dir(f4x4 a,f3 b)
{
    f4 aa = f4_mul_f4x4(f4_create(b.x,b.y,b.z,0) ,f4x4_transpose(a));
	return f3_create(aa.x,aa.y,aa.z);
}

f3 fmj_3dtrans_transform_p(f4x4 a,f3 b)
{
    f4 aa = f4_mul_f4x4(f4_create(b.x,b.y,b.z,1), f4x4_transpose(a));
	return f3_create(aa.x,aa.y,aa.z);
}
