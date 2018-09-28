static char const *opt_help =
    "General Options\n"
    "    --h\n"
    "    --?\n"
    "    --help\n"
    "        displays this help text\n"
    "Slicing Options\n"
    "    --min=ARG\n"
    "        min slice z coord [mm] (default: use bounding box of model)\n"
    "    --max=ARG\n"
    "        max slice z coord [mm] (default: use bounding box of model)\n"
    "    --step=ARG\n"
    "        thickness of slice [mm] (default: 0.2)\n"
    "    --z=ARG\n"
    "        equivalent to --min COORD --max COORD\n"
    "Intermediate Stage Output/Alternative Output Format Options\n"
    "    --dump-syn\n"
    "        print after stage 1: AST of input file; don't slice\n"
    "    --dump-scad\n"
    "        print after stage 2: SCAD tree, SCAD format; don't slice\n"
    "    --dump-csg3\n"
    "        print after stage 3: 3D CSG model, SCAD format; don't slice\n"
    "    --dump-csg2\n"
    "        print after stage 4: final 2D polygon stack in SCAD format\n"
    "    --dump-ps\n"
    "        print after stage 4: final 2D polygon stack in PS format\n"
    "    --no-csg\n"
    "    --csg\n"
    "        for stage 4: do (not) run 2D boolean operation pass\n"
    "    --no-tri\n"
    "    --tri\n"
    "        for stage 4: do (not) run triangulation pass\n"
    "PostScript Output Options\n"
    "    --ps-scale-fit\n"
    "        for --dump-ps: expand to fit normal bounding box to page\n"
    "    --ps-scale-max\n"
    "        for --dump-ps: expand to fit maximum bounding box to page\n"
    "    --ps-no-single-page\n"
    "    --ps-single-page\n"
    "        (do not) print all layers to a single page, bottom to top\n"
    "    --ps-no-tri\n"
    "    --ps-tri\n"
    "        (do not) print triangle boundaries\n"
    "    --ps-no-path\n"
    "    --ps-path\n"
    "        (do not) print paths and points\n"
    "    --ps-no-mark\n"
    "    --ps-mark\n"
    "        (do not) mark the polygon inside with a mark\n"
    "    --ps-no-wire\n"
    "        same as --ps-no-tri --ps-no-path --ps-no-mark\n"
    "    --ps-rot-x=ARG\n"
    "        rotate about x axis by angle\n"
    "    --ps-rot-y=ARG\n"
    "        rotate about y axis by angle\n"
    "    --ps-rot-z=ARG\n"
    "        rotate about z axis by angle\n"
    "    --ps-scale=ARG\n"
    "        scale output on all axes\n"
    "    --ps-persp=ARG\n"
    "        perspective change (1 = 1m toward camera scales by 2)\n"
    "    --ps-color-path=ARG\n"
    "        RGB color of polygon paths\n"
    "    --ps-color-tri=ARG\n"
    "        RGB color of triangle boundaries\n"
    "    --ps-color-fill=ARG\n"
    "        RGB fill color of triangles\n"
    "    --ps-color-vertex=ARG\n"
    "        RGB color of vertices\n"
    "    --ps-color-mark=ARG\n"
    "        RGB color of internal mark\n"
    "Debugging Options\n"
#ifdef PSTRACE
    "    --debug-ps=ARG\n"
    "        set name of PostScript debug output file\n"
#endif
    "";
static void get_opt_help(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    help();
}

static void get_opt_csg(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->no_csg, name, arg);
}

static void get_opt_debug_ps(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *fn __unused)
{
#ifdef PSTRACE

    FILE *f = fopen(fn, "wt");
    if (f == NULL) {
        fprintf(stderr, "Error: Unable to open %s for writing: %s\n",
            fn, strerror(errno));
        my_exit(1);
    }
    cp_debug_ps_file = f;

    CP_CALLOC(cp_debug_ps);
    *cp_debug_ps = *CP_STREAM_FROM_FILE(f);

    cp_ps_doc_begin(cp_debug_ps,
        CP_SIZE_MAX,
        0, 0, CP_PS_PAPER_X, CP_PS_PAPER_Y);
#endif
}

static void get_opt_dump_csg2(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->dump_csg2, name, arg);
}

static void get_opt_dump_csg3(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->dump_csg3, name, arg);
}

static void get_opt_dump_ps(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->dump_ps, name, arg);
}

static void get_opt_dump_scad(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->dump_scad, name, arg);
}

static void get_opt_dump_syn(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->dump_syn, name, arg);
}

static void get_opt_max(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_dim(&opt->z_max, name, arg);
    opt->have_z_max = true;
}

static void get_opt_min(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_dim(&opt->z_min, name, arg);
    opt->have_z_min = true;
}

static void get_opt_no_csg(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->no_csg, name, arg);
}

static void get_opt_no_tri(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->no_tri, name, arg);
}

static void get_opt_ps_color_fill(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_rgb(&opt->ps.color_fill, name, arg);
}

static void get_opt_ps_color_mark(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_rgb(&opt->ps.color_mark, name, arg);
}

static void get_opt_ps_color_path(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_rgb(&opt->ps.color_path, name, arg);
}

static void get_opt_ps_color_tri(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_rgb(&opt->ps.color_tri, name, arg);
}

static void get_opt_ps_color_vertex(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_rgb(&opt->ps.color_vertex, name, arg);
}

static void get_opt_ps_mark(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->ps.no_mark, name, arg);
}

static void get_opt_ps_no_mark(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->ps.no_mark, name, arg);
}

static void get_opt_ps_no_path(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->ps.no_path, name, arg);
}

static void get_opt_ps_no_single_page(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->ps.single_page, name, arg);
}

static void get_opt_ps_no_tri(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->ps.no_tri, name, arg);
}

static void get_opt_ps_no_wire(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    opt->ps.no_tri = true;
    opt->ps.no_path = true;
    opt->ps.no_mark = true;
}

static void get_opt_ps_path(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->ps.no_path, name, arg);
}

static void get_opt_ps_persp(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_scale(&opt->ps_persp, name, arg);
}

static void get_opt_ps_rot_x(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    cp_angle_t a;
    get_arg_angle(&a, name, arg);
    cp_mat4_t m;
    cp_mat4_rot_x(&m, CP_SINCOS_DEG(a));
    cp_mat4_mul(&opt->ps.xform2, &m, &opt->ps.xform2);
}

static void get_opt_ps_rot_y(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    cp_angle_t a;
    get_arg_angle(&a, name, arg);
    cp_mat4_t m;
    cp_mat4_rot_y(&m, CP_SINCOS_DEG(a));
    cp_mat4_mul(&opt->ps.xform2, &m, &opt->ps.xform2);
}

static void get_opt_ps_rot_z(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    cp_angle_t a;
    get_arg_angle(&a, name, arg);
    cp_mat4_t m;
    cp_mat4_rot_z(&m, CP_SINCOS_DEG(a));
    cp_mat4_mul(&opt->ps.xform2, &m, &opt->ps.xform2);
}

static void get_opt_ps_scale(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    cp_scale_t s;
    get_arg_scale(&s, name, arg);
    cp_mat4_t m;
    cp_mat4_scale1(&m, s);
    cp_mat4_mul(&opt->ps.xform2, &m, &opt->ps.xform2);
}

static void get_opt_ps_scale_fit(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    opt->ps_scale_step = 1;
}

static void get_opt_ps_scale_max(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    opt->ps_scale_step = 2;
}

static void get_opt_ps_single_page(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_bool(&opt->ps.single_page, name, arg);
}

static void get_opt_ps_tri(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->ps.no_tri, name, arg);
}

static void get_opt_step(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_dim(&opt->z_step, name, arg);
}

static void get_opt_tri(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_neg_bool(&opt->no_tri, name, arg);
}

static void get_opt_z(
    cp_opt_t *opt __unused,
    char const *name __unused,
    char const *arg __unused)
{
    get_arg_dim(&opt->z_min, name, arg);
    opt->z_max = opt->z_min;
    opt->have_z_min = true;
    opt->have_z_max = true;
}

cp_get_opt_t opt_list[] = {
    {
        "?",
        get_opt_help,
        0,
    },
    {
        "csg",
        get_opt_csg,
        1,
    },
    {
        "debug-ps",
        get_opt_debug_ps,
        2,
    },
    {
        "dump-csg2",
        get_opt_dump_csg2,
        1,
    },
    {
        "dump-csg3",
        get_opt_dump_csg3,
        1,
    },
    {
        "dump-ps",
        get_opt_dump_ps,
        1,
    },
    {
        "dump-scad",
        get_opt_dump_scad,
        1,
    },
    {
        "dump-syn",
        get_opt_dump_syn,
        1,
    },
    {
        "h",
        get_opt_help,
        0,
    },
    {
        "help",
        get_opt_help,
        0,
    },
    {
        "max",
        get_opt_max,
        2,
    },
    {
        "min",
        get_opt_min,
        2,
    },
    {
        "no-csg",
        get_opt_no_csg,
        1,
    },
    {
        "no-tri",
        get_opt_no_tri,
        1,
    },
    {
        "ps-color-fill",
        get_opt_ps_color_fill,
        2,
    },
    {
        "ps-color-mark",
        get_opt_ps_color_mark,
        2,
    },
    {
        "ps-color-path",
        get_opt_ps_color_path,
        2,
    },
    {
        "ps-color-tri",
        get_opt_ps_color_tri,
        2,
    },
    {
        "ps-color-vertex",
        get_opt_ps_color_vertex,
        2,
    },
    {
        "ps-mark",
        get_opt_ps_mark,
        1,
    },
    {
        "ps-no-mark",
        get_opt_ps_no_mark,
        1,
    },
    {
        "ps-no-path",
        get_opt_ps_no_path,
        1,
    },
    {
        "ps-no-single-page",
        get_opt_ps_no_single_page,
        1,
    },
    {
        "ps-no-tri",
        get_opt_ps_no_tri,
        1,
    },
    {
        "ps-no-wire",
        get_opt_ps_no_wire,
        0,
    },
    {
        "ps-path",
        get_opt_ps_path,
        1,
    },
    {
        "ps-persp",
        get_opt_ps_persp,
        2,
    },
    {
        "ps-rot-x",
        get_opt_ps_rot_x,
        2,
    },
    {
        "ps-rot-y",
        get_opt_ps_rot_y,
        2,
    },
    {
        "ps-rot-z",
        get_opt_ps_rot_z,
        2,
    },
    {
        "ps-scale",
        get_opt_ps_scale,
        2,
    },
    {
        "ps-scale-fit",
        get_opt_ps_scale_fit,
        0,
    },
    {
        "ps-scale-max",
        get_opt_ps_scale_max,
        0,
    },
    {
        "ps-single-page",
        get_opt_ps_single_page,
        1,
    },
    {
        "ps-tri",
        get_opt_ps_tri,
        1,
    },
    {
        "step",
        get_opt_step,
        2,
    },
    {
        "tri",
        get_opt_tri,
        1,
    },
    {
        "z",
        get_opt_z,
        2,
    },
};