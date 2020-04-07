
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
    
void fmj_sprite_add_rect(FMJMemoryArena* arena,f3 p[],f4 colors[],f2 uv[])
{
    FMJMemoryArenaPushParams params = fmj_arena_push_params_default();
    params.flags = fmj_arena_push_params_flag_none;
    f32* v = (f32*)PUSHSIZE(arena,SIZE_OF_SPRITE_IN_BYTES,params);
    fmj_sprite_add_verts_(v,p,colors,uv);
}
