<h1 id="the-mish-project">The Mish Project</h1>
<p>This is the 42 Berlin School <code>minishell</code> project, written by [author 1][author 2], in accordance with the version number [version number] of the subject [include subject and link]. This project does not cover the bonus part of the subject. In total, it took us around four weeks to finish the whole thing.</p>
<h2 id="installation">Installation</h2>
<p>If you want to test our <code>minishell</code>, Mish, you can do so in both Linux and Max.</p>
<ul>
<li>Clone the repo into your system</li>
<li>run the <code>make</code> command and wait until <code>libft</code> is cloned and built</li>
<li>run <code>./minishell</code> to open Mish.</li>
</ul>
<h2 id="about-the-project">About the Project</h2>
<p>The <code>minishell</code> project requires students to develop a simple clone of Bash. It is also the first group project of the 42 Core Curriculum. From these two statements, we can easily identify the main challenges and goals of the task:</p>
<ul>
<li>Acquire a deep understanding of Bash inner workings.</li>
<li>Coordinate work with your teammate.</li>
</ul>
<p>We believe that without properly addressing and planning for these two challenges from the very beginning, <code>minishell</code> will quickly turn into what a lot of students call &quot;minihell.&quot;</p>
<h3 id="understanding-bash">Understanding Bash</h3>
<p>Released in 1989, Bash has by now acquired almost mythical status. It is a universal tool that every programmer should feel, at the very least, acquainted with, if not properly comfortable. Therefore, sources at your disposal are plenty. If you are a 42 student, we advise you to search Slack for resources provided by fellow students over the years. Be aware, the <code>minishell</code> subject has changed over time, so not all advice is relevant. Here is a list of some of the most mentioned and useful links:</p>
<ul>
<li>SOURCES</li>
</ul>
<p>In our experience, no amount of reading will actually prepare you for some of Bash&#39;s more obscure behaviors. And although a lot of them are out of the scope of the project, there&#39;s still plenty that needs to be considered, even if you do not go for the bonus. We encountered a lot of these difficult cases while testing our almost finished project. This is the most stressful way of discovering them. Luckily, by then our program was robust enough to withstand most of them.</p>
<p>Nevertheless, there are two available online spreadsheets that cover a huge amount of cases to test for. It is a good idea to go through most, if not all, of them at least once to test your <code>minishell</code>. Maybe a read before could avoid some issues down the line too. But <strong>be aware</strong>, a lot of the cases mentioned in these spreadsheets are out of scope, apply only for bonus or are outright wrong. Do not follow them blindly, but test each with Bash on your own.</p>
<ul>
<li>SPREADSHEETS</li>
</ul>
<h3 id="coordinating-teamwork">Coordinating Teamwork</h3>
<p>There was no great compleity regarding teamwork. Given the small size of the team and our generous time availability, we went through a simple workflow. Each change or bug fix was done inside a bransh of this repository, pushed, reviewd by the other author and merged. We could make this work because we communicated a lot, either through Slack or coding side by side.</p>
<p>Regardless of how you chose to organize work, you will need to communicate as much as possible and try to understand whats going on even inside the files you have not written.</p>
<h2 id="how-mish-works">How Mish Works</h2>
<p>After you&#39;ve read the listed sources, youll learn that Bash is composed of four distinct parts: the <code>parser</code>, the <code>tokenizer</code>, the <code>expander</code>, and the <code>executor</code>. Tokens are put into a tree, which is then executed in the appropiate order. This should probably be your layout if you are aiming for the bonus.</p>
<p>Otherwise things can be simplified a bit. Mish does not have a separate <code>expander</code>. Inside the <code>input_handler</code> directory .
There is no tree structure but a list of commands that gets executed from beginning to end.</p>
