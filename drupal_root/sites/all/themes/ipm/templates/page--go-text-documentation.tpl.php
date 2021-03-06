<!DOCTYPE html>
<html class="html">
 <head>

  <meta http-equiv="Content-type" content="text/html;charset=UTF-8"/>
  <meta name="generator" content="7.2.232.244"/>
  <title>Text Documentation</title>
  <!-- CSS -->
  <link rel="stylesheet" type="text/css" href="/sites/all/themes/ipm/GO/css/site_global.css?397963719"/>
  <link rel="stylesheet" type="text/css" href="/sites/all/themes/ipm/GO/css/master_a-master.css?4032003262"/>
  <link rel="stylesheet" type="text/css" href="/sites/all/themes/ipm/GO/css/text-documentation.css?51515139" id="pagesheet"/>
  <!-- Other scripts -->
  <script type="text/javascript">
   document.documentElement.className += ' js';
</script>
   </head>
 <body>

  <div class="clearfix" id="page"><!-- column -->
   <div class="clearfix colelem" id="pu460-5"><!-- group -->
    <div class="clearfix grpelem" id="u460-5"><!-- content -->
     <p><span id="u460">Genom</span><span id="u460-2">Analytics</span></p>
    </div>
    <ul class="MenuBar clearfix grpelem" id="menuu414"><!-- horizontal box -->
     <li class="MenuItemContainer clearfix grpelem" id="u422"><!-- vertical box -->
      <a class="nonblock nontext MenuItem MenuItemWithSubMenu clearfix colelem" id="u423" href="go-index"><!-- horizontal box --><div class="MenuItemLabel NoWrap clearfix grpelem" id="u424-4"><!-- content --><p>Home</p></div></a>
     </li>
     <li class="MenuItemContainer clearfix grpelem" id="u415"><!-- vertical box -->
      <a class="nonblock nontext MenuItem MenuItemWithSubMenu clearfix colelem" id="u416" href="go-workflow-examples"><!-- horizontal box --><div class="MenuItemLabel NoWrap clearfix grpelem" id="u418-4"><!-- content --><p>Workflow Examples</p></div></a>
     </li>
     <li class="MenuItemContainer clearfix grpelem" id="u429"><!-- vertical box -->
      <a class="nonblock nontext MenuItem MenuItemWithSubMenu clearfix colelem" id="u430" href="go-video-tutorials"><!-- horizontal box --><div class="MenuItemLabel NoWrap clearfix grpelem" id="u432-4"><!-- content --><p>Video Tutorials</p></div></a>
     </li>
     <li class="MenuItemContainer clearfix grpelem" id="u453"><!-- vertical box -->
      <a class="nonblock nontext MenuItem MenuItemWithSubMenu MuseMenuActive clearfix colelem" id="u456" href="go-text-documentation"><!-- horizontal box --><div class="MenuItemLabel NoWrap clearfix grpelem" id="u459-4"><!-- content --><p>Text Documentation</p></div></a>
     </li>
     <li class="MenuItemContainer clearfix grpelem" id="u446"><!-- vertical box -->
      <a class="nonblock nontext MenuItem MenuItemWithSubMenu clearfix colelem" id="u449" href="go-contact-us"><!-- horizontal box --><div class="MenuItemLabel NoWrap clearfix grpelem" id="u452-4"><!-- content --><p>Contact Us</p></div></a>
     </li>
    </ul>
   </div>
   <div class="clearfix colelem" id="u556-101"><!-- content -->
    <p id="u556-2">Upload Genome window</p>
    <p id="u556-3">&nbsp;</p>
    <p>The Upload Genome window allows a user to upload various types of datasets to the GenomOncology server and load the datasets into the GenomOncology application database.</p>
    <p>&nbsp;</p>
    <p>Clicking the Upload button launches a dialog allowing the user to select a file from their local system. They can select the file type, for example VCF, and select a folder in which to store the sample. If the file contains multiple samples then the user should select the Contains Multiple Samples checkbox. When this box is checked the application will create a new database record for each sample contained in the file. In addition to selecting the file and storage location, the user can also modify the default Genome Name. This is the name the system will use to identify the sample in the application database and display to the user. The user can also modify the Patient Name, which is an ID that the system will use to group multiple datasets from the same individual. The user may select any previously uploaded BAM files to associate with the dataset and may specify if the dataset is from a tumor or germ line sample.</p>
    <p>&nbsp;</p>
    <p>Uploaded samples appear in the data table in the main Upload Genome window. These samples are labeled “Ready to Process.” A user may select the samples they wish to load into the GenomOncology application and click the Process button. This causes the samples to be processed in real&#45;time and added to the application database. After the samples have been processed they are removed from the Upload Genome data table and are available for analysis.</p>
    <p>&nbsp;</p>
    <p id="u556-13">&nbsp;</p>
    <p id="u556-15"><span id="u556-14">Supported data types</span></p>
    <p>The following data types are supported in the GenomOncology application:</p>
    <p>&nbsp;</p>
    <p id="u556-20">DNAseq</p>
    <p>SNPs and Indels</p>
    <p>Structural Variation</p>
    <p>Copy Number Variation</p>
    <p>Loss of Heterozygosity Variation</p>
    <p>&nbsp;</p>
    <p id="u556-31">RNAseq</p>
    <p>SNPs and Indels</p>
    <p>Gene Expression</p>
    <p>Structural Variation</p>
    <p>&nbsp;</p>
    <p id="u556-40">Methylseq</p>
    <p>Differential Methylation analysis</p>
    <p>&nbsp;</p>
    <p id="u556-44">&nbsp;</p>
    <p id="u556-46"><span id="u556-45">Supported file formats</span></p>
    <p>The following file formats are supported in the GenomOncology application:</p>
    <p>&nbsp;</p>
    <p id="u556-51">.vcf</p>
    <p>GATK output .vcf</p>
    <p>mpileup output .vcf</p>
    <p>MuTect output .vcf</p>
    <p>Strelka output .vcf</p>
    <p>Ion Reporter output .vcf</p>
    <p>VarScan2 output .vcf</p>
    <p>Any additional .vcf following the depth and genotype encoding as in GATK output .vcf</p>
    <p>&nbsp;</p>
    <p id="u556-68">Complete Genomics format</p>
    <p id="u556-70">.gvf</p>
    <p id="u556-72">.gff</p>
    <p id="u556-74">ExomeCNV output</p>
    <p id="u556-76">VarScan2 .snp output files</p>
    <p id="u556-78">TCGA .maf files</p>
    <p id="u556-80">Regions in .bed format</p>
    <p id="u556-82">GenomOncology Gold Standard format files</p>
    <p id="u556-84">Phenotypic .tsv files</p>
    <p>&nbsp;</p>
    <p id="u556-87"><span id="u556-86">Supported Genome Builds</span></p>
    <p>The GenomOncology application currently only supports hg19/b37.</p>
    <p>&nbsp;</p>
    <p id="u556-92"><span id="u556-91">Missing or Reference Data</span></p>
    <p>When an uploaded file contains no informative data at a particular position (for example, a sample in a .vcf file having a genotype of ./.) or when the position is reported as being reference the GenomOncology application skips the position without creating a variant record at that location for the sample being processed.</p>
    <p>&nbsp;</p>
    <p id="u556-97"><span id="u556-96">Germ&#45;line and Tumor datasets</span></p>
    <p>The GenomOncology application includes a germ&#45;line/tumor designation for each uploaded dataset. Datasets with the same Patient Name, and at least one tumor sample, are automatically grouped in a sub&#45;folder labeled with the Patient Name in the Browse Genomes window. The sub&#45;folder also contains an automatically created dataset labeled Tumor Normal Pair. This automatic dataset is a digital subtraction of the germ&#45;line variants from the tumor sample. It allows the user to analyze variants unique to the Tumor sample.</p>
   </div>
   <div class="verticalspacer"></div>
  </div>
  <!-- JS includes -->
  <script type="text/javascript">
   if (document.location.protocol != 'https:') document.write('\x3Cscript src="http://musecdn.businesscatalyst.com/scripts/4.0/jquery-1.8.3.min.js" type="text/javascript">\x3C/script>');
</script>
  <script type="text/javascript">
   window.jQuery || document.write('\x3Cscript src="/sites/all/themes/ipm/GO/scripts/jquery-1.8.3.min.js" type="text/javascript">\x3C/script>');
</script>
  <script src="/sites/all/themes/ipm/GO/scripts/museutils.js?3880880085" type="text/javascript"></script>
  <script src="/sites/all/themes/ipm/GO/scripts/jquery.musemenu.js?32367222" type="text/javascript"></script>
  <script src="/sites/all/themes/ipm/GO/scripts/jquery.watch.js?4199601726" type="text/javascript"></script>
  <!-- Other scripts -->
  <script type="text/javascript">
   $(document).ready(function() { try {
Muse.Utils.transformMarkupToFixBrowserProblemsPreInit();/* body */
Muse.Utils.prepHyperlinks(true);/* body */
Muse.Utils.initWidget('.MenuBar', function(elem) { return $(elem).museMenu(); });/* unifiedNavBar */
Muse.Utils.fullPage('#page');/* 100% height page */
Muse.Utils.showWidgetsWhenReady();/* body */
Muse.Utils.transformMarkupToFixBrowserProblems();/* body */
} catch(e) { Muse.Assert.fail('Error calling selector function:' + e); }});
</script>
   </body>
</html>
