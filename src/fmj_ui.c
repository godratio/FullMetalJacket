
f2 fmj_ui_get_rect_dim(FMJUIRect rect)
{
    return f2_create(rect.dim.right - rect.dim.left, rect.dim.bottom - rect.dim.top );
}

void fmj_ui_calculate_rect_dim(FMJUIRect* child_rect,FMJUIRect parent_rect)
{
	f2 grd = fmj_ui_get_rect_dim(parent_rect);
    f4 parent_size = f4_create(grd.x,grd.y,grd.x,grd.y);

	f4 a = f4_add(child_rect->anchor,child_rect->offset);
    f4 xyxy = f4_create(parent_rect.dim.x,parent_rect.dim.y,parent_rect.dim.x,parent_rect.dim.y);
    f4 xyxy_size = f4_create(parent_size.x,parent_size.y,parent_size.x,parent_size.y);    
	f4 b = f4_add(xyxy,xyxy_size);    

    child_rect->dim = f4_mul(a,b);
    //child_rect->dim.x = parent_rect.dim.x + parent_size.x * child_rect->anchor.x + child_rect->offset.x;
    //child_rect->dim.y = parent_rect.dim.y + parent_size.y * child_rect->anchor.y + child_rect->offset.y;
    //child_rect->dim.z = parent_rect.dim.x + parent_size.x * child_rect->anchor.z + child_rect->offset.z;
    //child_rect->dim.w = parent_rect.dim.y + parent_size.y * child_rect->anchor.w + child_rect->offset.w;
}

void fmj_ui_get_rect_dim_from_p(FMJUIRect* child_rect,FMJUIRect parent_rect,f3 p,f2 dim)
{
    f2 parent_size = fmj_ui_get_rect_dim(parent_rect);

	f4 a = f4_create(dim.x,dim.y,dim.x,dim.y);
	f4 b = f4_create(p.x,p.y,p.x,p.y);
	f4 c = f4_add(a,b);
	f2 d = f2_add(f2_create(c.y,c.z),f2_create(dim.y,dim.x));

	child_rect->dim = f4_create(c.x,d.x,d.y,c.w);// (a + b);
	
    //child_rect->dim.x = parent_rect.dim.x + p.x;
    //child_rect->dim.y = parent_rect.dim.y + p.y + dim.y;
    //child_rect->dim.z = parent_rect.dim.x + p.x + dim.x;
    //child_rect->dim.w = parent_rect.dim.y + p.y;
}

void fmj_ui_evaluate_node(FMJUINode* node,FMJUIHotNodeState* hot_node_state)
{
//    hot_node_state->prev_node = hot_node_state->node;
//    hot_node_state->node = 0;
    for(int i = 0;i < node->children.fixed.count;++i)
    {
        FMJUINode* child_node = fmj_stretch_buffer_check_out(FMJUINode,&node->children,i);
        if(child_node)
        {
            if(child_node->use_anchor)
            {
                fmj_ui_calculate_rect_dim(&child_node->rect,node->rect);
            }

            child_node->rect.current_color = child_node->rect.color;                    

            //TODO(Ray):for not only hot node at a time
            f2 mouse_p = hot_node_state->mouse_p;
            if(mouse_p.x > child_node->rect.dim.x &&
               mouse_p.x < child_node->rect.dim.z &&
               mouse_p.y < child_node->rect.dim.y &&
               mouse_p.y > child_node->rect.dim.w &&
               child_node->interactable)
            {
                hot_node_state->node = child_node;
                hot_node_state->node->rect.current_color = hot_node_state->node->rect.highlight_color;
            }
            fmj_ui_evaluate_node(child_node,hot_node_state);
        }
        fmj_stretch_buffer_check_in(&node->children);
    }
}

void fmj_ui_evaluate_on_node_recursively(FMJUINode* node,void (*eval_func)(void*))
{
    for(int i = 0;i < node->children.fixed.count;++i)
    {
        FMJUINode* child_node = fmj_stretch_buffer_check_out(FMJUINode,&node->children,i);
        if(child_node)
        {
            (*eval_func)(child_node);
            fmj_ui_evaluate_on_node_recursively(child_node,eval_func);
        }
        fmj_stretch_buffer_check_in(&node->children);
    }

}
