
FMJSprite fmj_sprite_init(u32 tex_id,f2 uvs[],f4 color,bool is_visible)
{
    FMJSprite result = {0};
    result.tex_id = tex_id;
    for(int i = 0;i < 4;++i)
    {
        result.uvs[i] = uvs[i];
    }
    result.color = color;
    result.is_visible = is_visible;
    return result;
}

void fmj_sprite_add_verts_(f32* v,f3 p[],f4 colors[],f2 uv[])
{
    u32 i = 0;
    f3 v1 =  p[0];
    v[i++] = v1.x;
    v[i++] = v1.y;
    v[i++] = v1.z;
        
    v[i++] = colors[0].r;
    v[i++] = colors[0].g;
    v[i++] = colors[0].b;
    v[i++] = colors[0].a;
        
    v[i++] = uv[0].x;
    v[i++] = uv[0].y;
        
    //vertex 1
    f3 v2 = p[1];
    v[i++] = v2.x;
    v[i++] = v2.y;
    v[i++] = v2.z;
        
    v[i++] = colors[1].r;
    v[i++] = colors[1].g;
    v[i++] = colors[1].b;
    v[i++] = colors[1].a;
        
    v[i++] = uv[1].x;
    v[i++] = uv[1].y;
        
    //vertex 2
    f3 v3 = p[2];
    v[i++] = v3.x;
    v[i++] = v3.y;
    v[i++] = v3.z;
        
    v[i++] = colors[2].r;
    v[i++] = colors[2].g;
    v[i++] = colors[2].b;
    v[i++] = colors[2].a;
        
    v[i++] = uv[2].x;
    v[i++] = uv[2].y;
        
    //Tri 2
    //vertex 3
    f3 v4 = p[0];
    v[i++] = v4.x;
    v[i++] = v4.y;
    v[i++] = v4.z;
        
    v[i++] = colors[0].r;
    v[i++] = colors[0].g;
    v[i++] = colors[0].b;
    v[i++] = colors[0].a;
        
    v[i++] = uv[0].x;
    v[i++] = uv[0].y;
        
    //vertex 4
    f3 v5 = p[2];
    v[i++] = v5.x;
    v[i++] = v5.y;
    v[i++] = v5.z;
        
    v[i++] = colors[2].r;
    v[i++] = colors[2].g;
    v[i++] = colors[2].b;
    v[i++] = colors[2].a;
        
    v[i++] = uv[2].x;
    v[i++] = uv[2].y;
        
    //vertex 5
    f3 v6 = p[3];
    v[i++] = v6.x;
    v[i++] = v6.y;
    v[i++] = v6.z;
        
    v[i++] = colors[3].r;
    v[i++] = colors[3].g;
    v[i++] = colors[3].b;
    v[i++] = colors[3].a;
        
    v[i++] = uv[3].x;
    v[i++] = uv[3].y;
}
    
void fmj_sprite_add_quad_(f32* v,f3 p,quaternion r,f2 dim,f4 color,f2 uv[])
{
    f2 x_axis = f2_create(1,0);
    f2 y_axis = f2_create(0,1);
    f2 half_dim = f2_mul_s(dim,0.5f);
    f2 p2 = f2_create(p.x,p.y);
    f2 minp = f2_add(p2,f2_create(-half_dim.x,-half_dim.y));
//    f2 maxp = minp + dim.x() * x_axis + dim.y() * y_axis;
    f2 a = f2_s_mul(dim.x,x_axis);
    f2 b = f2_s_mul(dim.y,y_axis);
    f2 maxp = f2_add(f2_add(minp,a),b);
                     
    u32 i = 0;
    f32 z = p.z;
        
    //TRi 1
    //vertex 0
    f3 v1r = f3_rotate(r,f3_create(-half_dim.x,-half_dim.y,0));
    f2 v1 = f2_add(f2_create(v1r.x,v1r.y),p2);
    //vertex 1
    f3 v2r = f3_rotate(r,f3_create(half_dim.x,-half_dim.y,0));
    f2 v2 =  f2_add(f2_create(v2r.x,v2r.y),p2);
    //vertex 2
    f3 v3r = f3_rotate(r,f3_create(half_dim.x,half_dim.y,0));    
    f2 v3 = f2_add(f2_create(v3r.x,v3r.y),p2);
    //vertex 5
    f3 v4r = f3_rotate(r,f3_create(-half_dim.x,half_dim.y,0));    
    f2 v4 =  f2_add(f2_create(v4r.x,v4r.y),p2);
    
    f3 ps[4];
    ps[0] = f3_create(v1.x,v1.y,z);
    ps[1] = f3_create(v2.x,v2.y,z);
    ps[2] = f3_create(v3.x,v3.y,z);
    ps[3] = f3_create(v4.x,v4.y,z);
        
    f4 colors[4];
    colors[0] = color;
    colors[1] = color;
    colors[2] = color;
    colors[3] = color;
        
    fmj_sprite_add_verts_(v,ps,colors,uv);
}
    
void fmj_sprite_add_rect(FMJMemoryArena* arena,f3 p[],f4 colors[],f2 uv[])
{
    FMJMemoryArenaPushParams params = fmj_arena_push_params_default();
    params.flags = fmj_arena_push_params_flag_none;
    f32* v = (f32*)PUSHSIZE(arena,SIZE_OF_SPRITE_IN_BYTES,params);
    fmj_sprite_add_verts_(v,p,colors,uv);
}

void fmj_sprite_add_quad(FMJMemoryArena* arena,f3 p,quaternion r,f3 scale,f4 colors,f2 uv[])
{
    FMJMemoryArenaPushParams params = fmj_arena_push_params_default();
    params.flags = fmj_arena_push_params_flag_none;
    f32* v = (f32*)PUSHSIZE(arena,SIZE_OF_SPRITE_IN_BYTES,params);
    fmj_sprite_add_quad_(v,p,r,f2_create(scale.x,scale.y),colors,uv);
}

