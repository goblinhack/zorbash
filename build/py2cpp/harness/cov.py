import sys, os, ast, importlib.util, collections
sys.path.insert(0,"/home/claude/work"); sys.path.insert(0,"/home/claude/work/harness")
import callback_harness as ch, make_harness as mh, py2cpp
prog=py2cpp.Program(mh.PYROOT,mh.SRC,mh.WORK,mh.ORIG); prog.load(); prog.build_sigs(); prog.assign_kinds(); prog.infer_all()
import random as pyr
def choice(seq):
    _,h=ch.world_call("random_choice","",None); return seq[(h>>3)%len(seq)]
pyr.choice=choice
tpmod=type(sys)("tp"); tpmod.Tp=lambda *a: None
class Any(ch.MyMod):
    def __getattr__(self,n):
        if n in mh.TP_SETTERS or n in py2cpp.TILE_FUNCS: return lambda *a,**k: None
        return ch.MyMod.__getattr__(self,n)
sys.modules["my"]=Any(); sys.modules["tp"]=tpmod
for d in [mh.PYROOT]+[os.path.join(mh.PYROOT,"things",x) for x in os.listdir(mh.PYROOT+"/things")]: sys.path.append(d)
ch.World.enabled=False
mods={}; files={}
for m in prog.modules:
    p=os.path.join(mh.PYROOT,m.relpath)
    spec=importlib.util.spec_from_file_location(m.stem+"__cov",p); mod=importlib.util.module_from_spec(spec); spec.loader.exec_module(mod)
    mods[m.relpath]=mod; files[os.path.realpath(p)]=m.relpath
hit=collections.defaultdict(set)
def tracer(frame,event,arg):
    fn=frame.f_code.co_filename
    if fn in files:
        def local(fr,ev,a):
            if ev=="line": hit[fn].add(fr.f_lineno)
            return local
        hit[fn].add(frame.f_lineno)
        return local
    return None
ch.World.enabled=True
sys.settrace(tracer)
for line in open("/tmp/harness2/vectors.txt"):
    stem,fn,rel,*args=line.split(); ch.World.counter=0; ch.World.log=[]
    try: getattr(mods[rel],fn)(*[int(a) for a in args])
    except Exception: pass
sys.settrace(None)
tot=cov=0; per=[]
for m in prog.modules:
    p=os.path.realpath(os.path.join(mh.PYROOT,m.relpath))
    for f in prog.active_funcs(m):
        sig=prog.sigs[(m.relpath,f.name)]
        if not prog.eligible(sig): continue
        lines={n.lineno for n in ast.walk(f) if isinstance(n,ast.stmt) and not isinstance(n,(ast.FunctionDef,))}
        h=hit[p]&lines
        tot+=len(lines); cov+=len(h)
        if len(h)<len(lines): per.append((len(lines)-len(h),m.relpath,f.name))
print(f"statement coverage of registered callbacks: {cov}/{tot} = {100*cov/tot:.1f}%")
per.sort(reverse=True); print("least covered:",per[:6])
