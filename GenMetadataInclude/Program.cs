using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Collections.ObjectModel;

namespace GenMetadataInclude
{
    // Code is not meant to be readable.
    // PURPOSE: Autogenerate deps for il2cpp include header
    // Dont touch, my spaghetty - Danny parker
    // No like seriously, this tool it shit, dont use it.
    // This is a SCRIPT not a program. Its pretty much a hackfile

    public class hack
    {
        public string dir;
        public bool ImStd;
    }
    public class HeaderDeps
    {
        public float FolderVer;
        public Dictionary<hack, hack> HeaderList = new Dictionary<hack, hack>();
    }

    class Program
    {
        static HeaderDeps plzwork;
        static string[] Headers = { @"libil2cpp\vm\MetadataCache.cpp" };
        static string MetDirs = AppDomain.CurrentDomain.BaseDirectory + @"..\..\..\Extern\il2cpp\";

        public static string UnixToWindowsPath(string UnixPath)
        {
            return UnixPath.Replace("/", "\\");
        }

        static void Main(string[] args)
        {
            foreach (var dir in Directory.GetDirectories(MetDirs))
            {
                bool hasMinor = false;
                if (dir.Contains('.'))
                {
                    hasMinor = true;
                }

                foreach (var hdr in Headers)
                {
                    string hdrDir = dir + "\\" + hdr;

                    var file = File.ReadAllLines(hdrDir);

                    string[] folders = dir.Split('\\');
                    string folder = folders[folders.Length - 1];

                    float ver = float.Parse(folder);
                    plzwork = new HeaderDeps();
                    var ihatethis = new Dictionary<string, string>();
                    GetHeaderDeps(ref file, dir, ver, hdr);
                    string fuckthis = new DirectoryInfo(dir).FullName;
                    foreach (var xd in plzwork.HeaderList)
                    {
                        bool stdye = xd.Key.ImStd | xd.Value.ImStd;
                        if (stdye)
                        {
                            try { ihatethis.Add("<" + xd.Key.dir + ">", "<" + xd.Value.dir + ">"); }
                            catch (Exception) { }
                            continue;
                        }

                        var prc = new FileInfo(fuckthis + "\\" + xd.Key.dir);
                        var ilovechina = new FileInfo(fuckthis + "\\" + xd.Value);

                        var stringy = prc.FullName.Substring(fuckthis.Length + 1);
                        var cheese = prc.FullName.Substring(fuckthis.Length + 1);

                        try { ihatethis.Add(stringy, cheese); }
                        catch (Exception) { }

                    }
                    // YAY TIME TO PARSE!!!

                    string help;
                    string me;
                    switch (ver)
                    {
                        case 23.0f:
                            help = "#if MAPI_MVER == 23\n";
                            me = "#endif\n";
                            break;

                        case 24.0f:
                            help = "#if MAPI_MVER == 24\n#if MAPI_REV == 0\n"; ;
                            me = "#endif\n#endif\n";
                            break;

                        case 24.1f:
                            help = "#if MAPI_MVER == 24\n#if MAPI_REV == 1\n"; ;
                            me = "#endif\n#endif\n";
                            break;

                        case 24.2f:
                            help = "#if MAPI_MVER == 24\n#if MAPI_REV == 2\n"; ;
                            me = "#endif\n#endif\n";
                            break;

                        default:
                            throw new Exception("Shit and cry");
                    }

                    string wario = "";
                    foreach(var lol in ihatethis)
                    {
                        var unixyay = lol.Key.Replace('\\', '/');

                        if(unixyay[0] == '<')
                        {
                            wario += "#include " + unixyay + "\n";
                            continue;
                        }
                        if(ver > 23)
                        {
                            wario += "#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, " + unixyay + ")\n";
                        }
                        else
                        {
                            wario += "#include IL2CPP_INCLUDE(MAPI_MVER, " + unixyay + ")\n";
                        }
                    }

                    Console.WriteLine(help + wario + me);
                    Console.WriteLine("\n\n\n\n\n\n\n\n\n");

                    int x = 5;
                }
            }

            int y = 5;
        }


        //
        static void GetHeaderDeps(ref string[] hdr, string dir, float ver, string parentHdr)
        {
            for (int i = 0; i < hdr.Length; i++)
            {
                string line = hdr[i];
                if (line.Contains("#include"))
                {
                    if (i > 0)
                    {
                        string prevline = hdr[i - 1];
                        if (prevline.Contains("elif"))
                        {
                            continue;
                        }
                        if (prevline.Contains("else"))
                        {
                            continue;
                        }
                        if (prevline.Contains("ifdef"))
                        {
                            continue;
                        }
                    }
                    if (line.StartsWith("//"))
                    {
                        continue;
                    }
                    if (line.Contains("//"))
                    {
                        line = line.Substring(0, line.IndexOfAny("//".ToCharArray()));
                    }

                    string header = line.TrimStart();
                    header = header.TrimEnd();
                    header = header.Trim("#include".ToCharArray());

                    if (header.Contains('<'))
                    {
                        // System header
                        header = header.Replace("<", string.Empty);
                        header = header.Replace(">", string.Empty);
                        header = header.TrimStart();
                        hack h = new hack();
                        h.dir = header;
                        h.ImStd = true;
                        try { plzwork.HeaderList.Add(h, h); }
                        catch (ArgumentException) { }

                    }
                    else
                    {
                        header = header.Replace("\"", string.Empty);
                        header = header.TrimStart();

                        string FUCKINGWORK = dir + "\\libil2cpp" + parentHdr;
                        if (File.Exists(FUCKINGWORK))
                        {
                            string REEEEEE = Path.GetDirectoryName(FUCKINGWORK) + "\\" + Path.GetFileName(FUCKINGWORK);
                            string[] file = File.ReadAllLines(FUCKINGWORK);
                            string pth = REEEEEE.Substring(dir.Length + 1);
                            GetHeaderDeps(ref file, dir, ver, pth);
                        }

                        // First check if in cd
                        string parent = dir + "\\" + parentHdr;
                        string cd = parent + "\\..";
                        cd = UnixToWindowsPath(cd);

                        if (!Directory.Exists(cd))
                        {
                            goto xd;
                        }

                        try
                        {
                            string[] phdrs = Directory.GetFiles(cd, header, SearchOption.TopDirectoryOnly);
                            if (phdrs == null || phdrs.Length == 0)
                            {
                                goto xd;
                            }
                            else if (phdrs.Count() > 1)
                            {
                                throw new Exception("This shouldn't happen 3");
                            }
                            else
                            {
                                if (!File.Exists(phdrs[0]))
                                {
                                    throw new Exception("This shouldn't happen 4");
                                }
                                string REEEEEE = Path.GetDirectoryName(phdrs[0]) + "\\" + Path.GetFileName(phdrs[0]);
                                string[] file = File.ReadAllLines(phdrs[0]);
                                string pth = REEEEEE.Substring(dir.Length + 1);
                                GetHeaderDeps(ref file, dir, ver, pth);

                                hack h = new hack();
                                h.dir = pth;
                                h.ImStd = false;
                                try { plzwork.HeaderList.Add(h, h); }
                                catch (ArgumentException) { }

                                continue;
                            }
                        }
                        catch (Exception)
                        {
                            goto xd;
                        }

                        xd:

                        header = header.Replace("../", string.Empty);
                        if (header.Contains("google"))
                        {
                            continue;
                        }
                        string[] pheaders = Directory.GetFiles(dir, "libil2cpp\\" + header, SearchOption.AllDirectories);
                        if (pheaders == null || pheaders.Length == 0)
                        {
                            continue;
                        }
                        else if (pheaders.Count() > 1)
                        {
                            throw new Exception("This could happen");
                        }
                        else
                        {
                            if (!File.Exists(pheaders[0]))
                            {
                                throw new Exception("This shouldn't happen 2");
                            }
                            string REEEEEE = Path.GetDirectoryName(pheaders[0]) + "\\" + Path.GetFileName(pheaders[0]);
                            string[] file = File.ReadAllLines(pheaders[0]);
                            string headnmm = pheaders[0];
                            string pth = REEEEEE.Substring(dir.Length + 1);

                            GetHeaderDeps(ref file, dir, ver, pth);

                            hack h = new hack();
                            h.dir = pth;
                            h.ImStd = false;
                            try { plzwork.HeaderList.Add(h, h); }
                            catch (ArgumentException) { }

                            continue;
                        }
                    }

                }
            }
        }

    }
}
